#pragma once

#include "Settings/Setting.h"
#include "Settings/WalkthroughType.h"
#include "Files/DDFile.h"
#include "Files/job.h"
#include "Ghost/FirmwareVersion.h"
#include "Ghost/GhostGunner.h"
#include "Ghost/Display/LineType.h"
#include "Common/LockUtility.h"
#include "MillingStatus.h"
#include "RestClient/AvailableFirmware.h"
#include "RestClient/CustServiceReqError.h"

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <atomic>

enum EGhostGunnerStatus
{
	connectionFailed = -1,
	notConnected = 0,
	connecting = 1,
	connected = 2
};

/*
* Daemon that runs in the background and provides an API for the front-end electron application to communicate with.
*/
class DDCutDaemon
{
public:
	//////////////////////////////////////////////////////
	// Daemon
	//////////////////////////////////////////////////////
	
	// Gets the singleton instance of the daemon.
	static DDCutDaemon& GetInstance();

	void Initialize();

	void Shutdown();



	//////////////////////////////////////////////////////
	// DDFile
	//////////////////////////////////////////////////////

	// Gets the currently selected .dd file.
	DDFile* GetDDFile() const;

	// Sets the currently selected .dd file to the given path. Returns true if successful.
	bool SetDDFile(const std::string& ddFilePath) const;

	// Returns true if the .dd file has at least one job.
	bool IsValidDDFile(const std::string& ddFilePath) const;



	//////////////////////////////////////////////////////
	// GhostGunner
	//////////////////////////////////////////////////////

	// Gets the status of the connection to the GhostGunner.
	EGhostGunnerStatus GetGhostGunnerStatus() const;

	// Searches for GhostGunners connected through USB.
	std::list<GhostGunner> GetAvailableGhostGunners() const;

	// Sets the selected GhostGunner. Returns true if successful.
	bool SetSelectedGhostGunner(const GhostGunner& ghostGunner);

	// Determines if the given GhostGunner is the selected one.
	bool IsSelectedGhostGunner(const GhostGunner& ghostGunner) const;



	//////////////////////////////////////////////////////
	// Jobs
	//////////////////////////////////////////////////////
	std::vector<Job> GetJobs() const;

	Job* GetSelectedJob() const;

	bool SelectJob(const size_t jobIndex) const;



	//////////////////////////////////////////////////////
	// FeedRate
	//////////////////////////////////////////////////////

	int GetFeedRate() const;

	bool SetFeedRate(const int feedRate);



	//////////////////////////////////////////////////////
	// Firmware
	//////////////////////////////////////////////////////

	// Begins uploading firmware to the GhostGunner asynchronously.
	bool UploadFirmware(const AvailableFirmware& firmware);

	// The status of the firmware upload. 0-100 indicates the percentage completed. -1 indicates a failure during upload.
	int GetFirmwareUploadStatus() const;

	// Returns the firmware version of the currently connected GhostGunner.
	FirmwareVersion GetFirmwareVersion() const;

	// Checks for firmware updates, and returns all available updates for the user to choose.
	std::vector<AvailableFirmware> GetAvailableFirmwareUpdates() const;



	//////////////////////////////////////////////////////
	// Settings
	//////////////////////////////////////////////////////

	bool GetEnableSlider() const;
	bool GetPauseAfterGCode() const;
	int GetMinFeedRate() const;
	int GetMaxFeedRate() const;
	int GetTimeout() const;

	// Replaces the currently saved settings with the ones passed in.
	bool UpdateSettings(const std::list<Setting>& settings) const;



	//////////////////////////////////////////////////////
	// Navigation
	//////////////////////////////////////////////////////

	std::vector<Operation> GetAllSteps() const;

	std::unique_ptr<Operation> GetStep(const int stepIndex) const;

	bool StartMilling(const int stepIndex) const;

	// Gets the status of the milling for the given step. 0-100 indicates the percentage completed. -1 indicates a failure during upload.
	MillingStatus GetMillingStatus(const int stepIndex) const;

	std::vector<std::pair<ELineType, std::string>> GetReadWrites() const;

	bool EmergencyStop() const;


	//////////////////////////////////////////////////////
	// Walkthroughs
	//////////////////////////////////////////////////////

	// Determines if the given walkthrough should display. For example, if WalkthroughType == editor, this will return true if this is the first time using the editor.
	bool ShouldWalkthroughDisplay(const EWalkthroughType& walkthroughType) const;

	// Sets the given walkthrough as displayed, so it is not automatically displayed the next time the user takes the same action.
	void SetShowWalkthrough(const EWalkthroughType& walkthroughType, const bool show);



	//////////////////////////////////////////////////////
	// Miscellaneous
	//////////////////////////////////////////////////////

	// Sends a customer support request with the given message.
	std::unique_ptr<CustServiceReqError> SendCustomerSupportRequest(const std::string& email, const std::string& message, const bool includeLogs) const;

	std::string GetLogPath() const;

private:
	DDCutDaemon();
	~DDCutDaemon();
	std::atomic_bool m_shutdown = false;
	EGhostGunnerStatus m_connectionStatus = notConnected;
	HANDLE m_lockHandle;
	int m_nextFirmwareUpdateId;
};
