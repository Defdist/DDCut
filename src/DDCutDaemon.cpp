#include "DDCutDaemon.h"

#include "Common/defines.h"
#include "Settings/SettingManager.h"
#include "Ghost/ConnectionInitializer.h"
#include "Ghost/GhostGunnerManager.h"
#include "Ghost/Display/GhostDisplayManager.h"
#include "Ghost/GhostGunnerFinder.h"
#include "Ghost/JobManager.h"
#include "Ghost/GhostFirmwareManager.h"
#include "Files/DDFileManager.h"
#include "DDLogger/DDLogger.h"
#include "Common/ThreadManager.h"
#include "RestClient/DDRestClient.h"
#include "RestClient/FileDownloader.h"
#include "DDUpdater/DDUpdater.h"

#include <thread>
#include <filesystem>

// TODO: This should always fail gracefully.

//////////////////////////////////////////////////////
// Daemon
//////////////////////////////////////////////////////

std::thread initializeThread;

// Auto-detect and connect to GhostGunner
void Thread_Connect(std::atomic_bool& shutdown, EGhostGunnerStatus& connectionStatus, const HANDLE lockHandle)
{
	ThreadManager::GetInstance().SetCurrentThreadName("CONNECT_THREAD");

	while (!shutdown)
	{
		if (LockUtility::ObtainLock(lockHandle))
		{
			if (connectionStatus == notConnected || connectionStatus == connectionFailed)
			{
				const std::list<GhostGunner> availableGhostGunners = GhostGunnerFinder().GetAvailableGhostGunners();
				if (!availableGhostGunners.empty())
				{
					// TODO: Handle multiple ghost gunners connected.
					const GhostGunner& ghostGunner = availableGhostGunners.front();
					//DDLogger::Log("Thread_Initialize() - GhostGunner Found - Path: " + ghostGunner.GetPath() + " Serial Number: " + ghostGunner.GetSerialNumber());
					GhostGunnerManager::GetInstance().SetSelectedGhostGunner(ghostGunner);
					connectionStatus = connecting;
				}
			}
			
			if (connectionStatus == connecting)
			{
				DDLogger::Log("Thread_Connect() - Connecting");
				GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();
				if (pConnection != nullptr)
				{
					connectionStatus = ConnectionInitializer().InitializeConnection(*pConnection) ? connected : connectionFailed;
				}

				DDLogger::Log("Thread_Connect() - " + std::to_string(connectionStatus));
			}
			
			if (connectionStatus == connected)
			{
				bool stillPluggedIn = false;

				GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();
				if (pConnection != nullptr)
				{
					const std::list<GhostGunner> pluggedInGhostGunners = GhostGunnerFinder().GetAvailableGhostGunners();
					for (auto iter = pluggedInGhostGunners.cbegin(); iter != pluggedInGhostGunners.cend(); iter++)
					{
						if (iter->GetPath() == pConnection->GetPath())
						{
							stillPluggedIn = true;
							break;
						}
					}
				}

				if (!stillPluggedIn)
				{
					DDLogger::Log("Thread_Connect() - GhostGunner unplugged");
					connectionStatus = notConnected;
				}
			}

			LockUtility::ReleaseLock(lockHandle);
		}

		Sleep(100);
	}
}

DDCutDaemon::DDCutDaemon()
	: m_nextFirmwareUpdateId(1)
{
}

DDCutDaemon::~DDCutDaemon()
{
	Shutdown();
}

DDCutDaemon& DDCutDaemon::GetInstance()
{
	static DDCutDaemon instance;
	return instance;
}

void DDCutDaemon::Initialize()
{
	ThreadManager::GetInstance().SetCurrentThreadName("MAIN_THREAD");
	DDLogger::Log("Initializing");

	// 1. Initialize Setting Manager (this will read and cache preferences)
	SettingManager& settingManager = SettingManager::GetInstance();

	m_lockHandle = LockUtility::CreateLock();
	initializeThread = std::thread(Thread_Connect, std::ref(m_shutdown), std::ref(m_connectionStatus), m_lockHandle);
}

void DDCutDaemon::Shutdown()
{
	if (!m_shutdown)
	{
		m_shutdown = true;

		if (initializeThread.joinable())
		{
			initializeThread.join();
		}

		DDLogger::Log("SHUTTING DOWN");
		DDCutDaemon::GetInstance().EmergencyStop(); // TODO: Call AbortJob, instead.
		DDLogger::Flush();
	}
}

//////////////////////////////////////////////////////
// DDFile
//////////////////////////////////////////////////////

DDFile* DDCutDaemon::GetDDFile() const
{
	return DDFileManager::GetInstance().GetSelectedFile();
}

bool DDCutDaemon::SetDDFile(const std::string& ddFilePath) const
{
	DDLogger::Log("DDCutDaemon::SetDDFile - " + ddFilePath);

	DDFile* pDDFile = new DDFile(ddFilePath);
	if (pDDFile->GetJobs().empty())
	{
		delete pDDFile;
		return false;
	}
	else
	{
		DDFileManager::GetInstance().SetSelectedFile(pDDFile);
		return true;
	}
}

bool DDCutDaemon::IsValidDDFile(const std::string& ddFilePath) const
{
	DDFile ddFile(ddFilePath);

	return !ddFile.GetJobs().empty();
}



//////////////////////////////////////////////////////
// GhostGunner
//////////////////////////////////////////////////////

EGhostGunnerStatus DDCutDaemon::GetGhostGunnerStatus() const
{
    return m_connectionStatus;
}

std::list<GhostGunner> DDCutDaemon::GetAvailableGhostGunners() const
{
	std::list<GhostGunner> availableGhostGunners;
	if (LockUtility::ObtainLock(m_lockHandle))
	{
		availableGhostGunners = GhostGunnerFinder().GetAvailableGhostGunners();
		LockUtility::ReleaseLock(m_lockHandle);
	}

	return availableGhostGunners;
}

bool DDCutDaemon::SetSelectedGhostGunner(const GhostGunner& ghostGunner)
{
	bool success = false;

	if (LockUtility::ObtainLock(m_lockHandle))
	{
		if (!GhostGunnerManager::GetInstance().IsSelectedGhostGunner(ghostGunner))
		{
			GhostGunnerManager::GetInstance().ShutdownGhostGunner(nullptr, nullptr);
			success = GhostGunnerManager::GetInstance().SetSelectedGhostGunner(ghostGunner);
			m_connectionStatus = connecting;
		}

		LockUtility::ReleaseLock(m_lockHandle);
	}

	return success;
}

bool DDCutDaemon::IsSelectedGhostGunner(const GhostGunner& ghostGunner) const
{
	return GhostGunnerManager::GetInstance().IsSelectedGhostGunner(ghostGunner);
}



//////////////////////////////////////////////////////
// Jobs
//////////////////////////////////////////////////////

std::vector<Job> DDCutDaemon::GetJobs() const
{
	DDFile* pSelectedFile = DDFileManager::GetInstance().GetSelectedFile();
	if (pSelectedFile != nullptr)
	{
		return pSelectedFile->GetJobs();
	}

	return std::vector<Job>();
}

bool DDCutDaemon::SelectJob(const size_t jobIndex) const
{
	DDLogger::Log("DDCutDaemon::SelectJob() - jobIndex:" + std::to_string(jobIndex));

	DDFile* pSelectedFile = DDFileManager::GetInstance().GetSelectedFile();
	if (pSelectedFile != nullptr)
	{
		const std::vector<Job>& jobs = pSelectedFile->GetJobs();
		if (jobs.size() > jobIndex)
		{
			// if (state.grbl_version.compare(jobs[0].getMinFirmwareVersion()) < 0) // TODO: Check minimum firmware version.
			JobManager::GetInstance().SetSelectedJob(jobs[jobIndex]);

			return true;
		}
	}

	return false;
}

Job* DDCutDaemon::GetSelectedJob() const
{
	return JobManager::GetInstance().GetSelectedJob();
}



//////////////////////////////////////////////////////
// FeedRate
//////////////////////////////////////////////////////

int DDCutDaemon::GetFeedRate() const
{
	int feedRate = -1;

	GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();
	if (pConnection != nullptr)
	{
		feedRate = pConnection->GetFeedRate();
	}

	DDLogger::Log("DDCutDaemon::GetFeedRate() - FeedRate: " + std::to_string(feedRate));

	return feedRate;
}

bool DDCutDaemon::SetFeedRate(const int feedRate)
{
	GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();
	if (pConnection != nullptr)
	{
		DDLogger::Log("DDCutDaemon::SetFeedRate() - FeedRate changed from " + std::to_string(pConnection->GetFeedRate()) + " to " + std::to_string(feedRate));
		pConnection->SetFeedRate(feedRate);
		return true;
	}

	return false;
}



//////////////////////////////////////////////////////
// Settings
//////////////////////////////////////////////////////

bool DDCutDaemon::GetEnableSlider() const
{
	return SettingManager::GetInstance().GetEnableSlider();
}

bool DDCutDaemon::GetPauseAfterGCode() const
{
	return SettingManager::GetInstance().GetPauseAfterGCode();
}

int DDCutDaemon::GetMinFeedRate() const
{
	return SettingManager::GetInstance().GetMinFeedRate();
}

int DDCutDaemon::GetMaxFeedRate() const
{
	return SettingManager::GetInstance().GetMaxFeedRate();
}

int DDCutDaemon::GetTimeout() const
{
	return SettingManager::GetInstance().GetTimeout();
}

bool DDCutDaemon::UpdateSettings(const std::list<Setting>& settings) const
{
	SettingManager::GetInstance().UpdateSettings(settings);
	return true;
}



//////////////////////////////////////////////////////
// Firmware
//////////////////////////////////////////////////////

bool DDCutDaemon::UploadFirmware(const AvailableFirmware& firmware)
{
	DDLogger::Log("DDCutDaemon::UploadFirmware() - Uploading firmware " + firmware.VERSION);

	GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();
	if (pConnection != nullptr && !firmware.FILES.empty())
	{
		std::thread uploadThread(GhostFirmwareManager::UploadFirmware, std::ref(*pConnection), firmware.FILES[0]);
		uploadThread.detach();

		return true;
	}

	return false;
}

int DDCutDaemon::GetFirmwareUploadStatus() const
{
	return GhostFirmwareManager::GetInstance().GetFirmwareUploadStatus();
}

FirmwareVersion DDCutDaemon::GetFirmwareVersion() const
{
	GhostConnection* connection = GhostGunnerManager::GetInstance().GetConnection();
	if (m_connectionStatus == connected && connection != nullptr)
	{
		return GhostFirmwareManager::GetInstance().GetFirmwareVersion(*connection);
	}

	return FirmwareVersion("", "");
}

std::vector<AvailableFirmware> DDCutDaemon::GetAvailableFirmwareUpdates() const
{
	DDLogger::Log("DDCutDaemon::GetAvailableFirmwareUpdates() - Checking for updates.");
	
	const std::string firmwareVersion = GetFirmwareVersion().ddVersion;

	return DDRestClient().CheckForFirmwareUpdates(DDCUT_VERSION, firmwareVersion.substr(0, 3) == "201" ? "1.0" : firmwareVersion);
}


//////////////////////////////////////////////////////
// Walkthroughs
//////////////////////////////////////////////////////

bool DDCutDaemon::ShouldWalkthroughDisplay(const EWalkthroughType& walkthroughType) const
{
	return SettingManager::GetInstance().GetShowWalkthrough(walkthroughType);
}

void DDCutDaemon::SetShowWalkthrough(const EWalkthroughType& walkthroughType, const bool show)
{
	SettingManager::GetInstance().SetShowWalkthrough(walkthroughType, show);
}


//////////////////////////////////////////////////////
// Miscellaneous
//////////////////////////////////////////////////////

std::unique_ptr<CustServiceReqError> DDCutDaemon::SendCustomerSupportRequest(const std::string& email, const std::string& message, const bool includeLogs) const
{
	DDLogger::Log("DDCutDaemon::SendCustomerSupportRequest() - Sending Request.");
	if (includeLogs)
	{
		const std::string logText = DDLogger::ReadLog();
		return DDRestClient().SendCustomerServiceRequest("NOT_IMPLEMENTED", email, message, DDCUT_VERSION, logText);
	}
	else
	{
		return DDRestClient().SendCustomerServiceRequest("NOT_IMPLEMENTED", email, message, DDCUT_VERSION, "<NO LOGS INCLUDED>");
	}
}

std::string DDCutDaemon::GetLogPath() const
{
	return DDLogger::GetLogPath();
}

std::unique_ptr<SoftwareUpdateStatus> DDCutDaemon::CheckForUpdates() const
{
	DDLogger::Log("DDCutDaemon::CheckForUpdates() - Checking for updates.");

	std::unique_ptr<SoftwareUpdateStatus> pSoftwareUpdateStatus = DDRestClient().CheckForSoftwareUpdates(DDCUT_VERSION);
	if (pSoftwareUpdateStatus != nullptr)
	{
		DDLogger::Log("DDCutDaemon::CheckForUpdates() - Latest Version: " + pSoftwareUpdateStatus->LATEST_VERSION);
	}

	return pSoftwareUpdateStatus;
}

bool DDCutDaemon::InstallUpdates()
{
	DDLogger::Log("DDCutDaemon::InstallUpdates() - Installing updates.");

	return DDUpdater().UpdateDDCut("ddcut2.exe", DDCUT_VERSION);
}


//////////////////////////////////////////////////////
// Navigation
//////////////////////////////////////////////////////

std::vector<Operation> DDCutDaemon::GetAllSteps() const
{
	const Job* pJob = JobManager::GetInstance().GetSelectedJob();
	if (pJob != nullptr)
	{
		return pJob->GetOperations();
	}

	return std::vector<Operation>();
}

std::unique_ptr<Operation> DDCutDaemon::GetStep(const int stepIndex) const
{
	JobManager& jobManager = JobManager::GetInstance();
	Job* pJob = jobManager.GetSelectedJob();
	if (pJob != nullptr)
	{
		return std::make_unique<Operation>(pJob->GetOperation(stepIndex));
	}

	return std::unique_ptr<Operation>(nullptr);
}

std::thread millingThread;
bool millingInProgress = false;

void Thread_StartMilling(HANDLE lockHandle, Job& job, Operation& operation)
{
	ThreadManager::GetInstance().SetCurrentThreadName("MILLING_THREAD");
	DDLogger::Log("MILLING THREAD - Start");

	GhostDisplayManager::Clear();
	if (LockUtility::ObtainLock(lockHandle))
	{
		GhostGunnerManager::GetInstance().ReadWriteCycle(&job, &operation);

		LockUtility::ReleaseLock(lockHandle);
	}
	millingInProgress = false;
	DDLogger::Log("MILLING THREAD - End");
}

bool DDCutDaemon::StartMilling(const int stepIndex) const
{
	if (m_connectionStatus == connected && !millingInProgress)
	{
		GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();
		if (pConnection != nullptr)
		{
			JobManager& jobManager = JobManager::GetInstance();
			Job* pJob = jobManager.GetSelectedJob();
			if (pJob != nullptr)
			{
				pConnection->clearCoordinates();

				Operation& operation = pJob->GetOperation(stepIndex);

				DDLogger::Log("DDCutDaemon::StartMilling() - Sending GCodeFile for operation with index: " + std::to_string(stepIndex));
				operation.Load();
				pConnection->send(operation.GetGCodeFile());

				if (millingThread.joinable())
				{
					millingThread.join();
				}

				millingInProgress = true;
				millingThread = std::thread(Thread_StartMilling, m_lockHandle, std::ref(*pJob), std::ref(operation));

				return true;
			}
		}
	}

	return false;
}

MillingStatus DDCutDaemon::GetMillingStatus(const int stepIndex) const
{
	if (millingInProgress)
	{
		GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();
		if (pConnection != nullptr)
		{
			JobManager& jobManager = JobManager::GetInstance();
			Job* pJob = jobManager.GetSelectedJob();
			if (pJob != nullptr)
			{
				Operation& operation = pJob->GetOperation(stepIndex);
				const double totalSize = operation.GetGCodeFile().getLines().size();
				const double queueSize = pConnection->queueSize();

				const int status = (int)(100 * ((totalSize - queueSize) / totalSize));
				return MillingStatus(inProgress, status == 100 ? 99 : status);
			}
		}

		return MillingStatus(failed, -1);
	}
	else
	{
		return MillingStatus(completed, 100);
	}
}

std::vector<std::pair<ELineType, std::string>> DDCutDaemon::GetReadWrites() const
{
	return GhostDisplayManager::GetLines();
}

bool DDCutDaemon::EmergencyStop() const
{
	GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();
	if (pConnection != nullptr)
	{
		pConnection->reset();
		return true;
	}

	return false;
}