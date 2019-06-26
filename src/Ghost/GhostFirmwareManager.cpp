#include "GhostFirmwareManager.h"

#include "GhostGunnerFinder.h"
#include "GhostConnection.h"
#include "GhostGunnerManager.h"
#include "JobManager.h"
#include "ConnectionInitializer.h"

#include <RestClient/FileDownloader.h>
#include <Files/DDFileManager.h>
#include <DDLogger/DDLogger.h>
#include <Common/FileUtility.h>
#include <Common/defines.h>
#include <Common/OSUtility.h>

#include <vector>
#include <filesystem>

#ifdef _WIN32
#include <Windows.h>
#endif

#define INFO_BUFFER_SIZE 32767

GhostFirmwareManager& GhostFirmwareManager::GetInstance()
{
	static GhostFirmwareManager instance;
	return instance;
}

FirmwareVersion GhostFirmwareManager::GetFirmwareVersion(GhostConnection& connection) const
{
	// 1. Check the cache to see if firmware version was already loaded.
	const std::string& serialNumber = connection.GetGhostGunner().GetSerialNumber();
	if (m_cachedFirmwareVersionsBySerialNumber.find(serialNumber) != m_cachedFirmwareVersionsBySerialNumber.end())
	{
		return m_cachedFirmwareVersionsBySerialNumber.find(serialNumber)->second;
	}

	// 2. SetGGParms()
	connection.SetGGParms();

	// 3. Ask GG for Firmware Version
	connection.WriteWithTimeout("$I\n", 300);

	const std::string response = connection.ReadLineAndFlush();
	DDLogger::Log("GhostFirmwareManager::GetFirmwareVersion() - Firmware Version returned: " + response);

	// 4. Parse GG's Response

	// [grbl1.0c.20160330, DD 2V7 20160929]
	const size_t grblStart = 5;
	const size_t grblEnd = response.find_first_of(',');
	const std::string grblVersion = response.substr(grblStart, grblEnd - grblStart);

	const size_t start = response.find_last_of("DD");
	const size_t vend = response.find_last_of("]");
	const std::string ddVersion = response.substr(start + 2, (vend - start) - 2);

	const FirmwareVersion version(grblVersion, ddVersion);

	// 5. Cache GG's Firmware Version
	m_cachedFirmwareVersionsBySerialNumber.insert({ serialNumber, version });

	return version;
}

bool GhostFirmwareManager::LoadFirmware(GhostConnection& connection, const std::string& hexFilePath)
{
	//int response = MessageBox(NULL, "WARNING! Upgrading the firmware will abort the current session. Do you wish to continue?.", "Upgrade Firmware", MB_ICONWARNING | MB_YESNO);

	// 1. Abort current job
	JobManager::GetInstance().AbortCurrentJob();

	// 2. Disconnect
	if (connection.IsConnected())
	{
		connection.reset();
		connection.disconnect();
	}

#ifdef _WIN32
    // 3. Determine directory of hexFile
	size_t found = hexFilePath.find_last_of("/\\");
	const std::string newDirectory = hexFilePath.substr(0, found);

    // 4. Determine hexFileName
	const std::string hexFileName = FileUtility::GetFileName(hexFilePath);
    
    // 5. Determine path // TODO: Path to what?
    const std::string execPath = OSUtility::GetExecPath();
    
	std::string path = execPath;
	found = path.find('\\', 0);
	path.insert(found + 1, "\"");

	size_t next = found + 2;
	while ((found = path.find('\\', next)) != std::string::npos) 
	{
		path.insert(found, "\"");
		path.insert(found + 2, "\"");
		next = found + 4;
	}
    
    // 6. Get system directory path
    TCHAR infoBuf[INFO_BUFFER_SIZE];
    GetSystemDirectory(infoBuf, INFO_BUFFER_SIZE);
    const std::string sysdir = infoBuf;
    
    // 7. Build command
    const std::string command = sysdir + "\\cmd.EXE /C " + path + "\"\\Drivers\\AVRdude\\avrdude.exe -U flash:w:..\\Firmware\\" + hexFileName + " :i -C \"" + execPath + "\\Drivers\\AVRdude\\avrdude.conf\" -v -p ATMEGA328P -b 115200 -c stk500 -P " + connection.GetPath();
    
    // 8. Execute command in new process
    DDLogger::Log("GhostFirmwareManager::LoadFirmware - Executing Command.");
    if (!OSUtility::ExecuteCommandInNewProcess(newDirectory, command))
	{
		return false;
	}

    // 9. Set firmware as loaded // TODO: SetHexLoad/GetHexLoad belongs in FirmwareManager, instead.
	//SettingManager::GetInstance().SetHexLoad(true);
	m_uploadStatus = 50;
	while (m_uploadStatus != 100)
	{
		m_uploadStatus += 2;
		Sleep(50);
	}

    // 10. Clear currently selected file
	DDFileManager::GetInstance().SetSelectedFile(nullptr);

	// 11. Clear cache
	m_cachedFirmwareVersionsBySerialNumber.clear();
#else
	// TODO: Implement this for mac
#endif

	// 12. Reconnect
	ConnectionInitializer().InitializeConnection(connection);

	return true;
}

void GhostFirmwareManager::UploadFirmware(GhostConnection& connection, const std::string firmwareURL)
{
	GhostFirmwareManager& firmwareManager = GetInstance();
	firmwareManager.m_uploadStatus = 5;

	std::error_code errorCode;
	auto currentPath = std::filesystem::current_path(errorCode);
	if (!errorCode)
	{
		const std::string path = currentPath.string() + "\\Firmware\\";
		std::filesystem::create_directories(path, errorCode);
		if (!errorCode)
		{
			const std::string fileName = firmwareURL.substr(firmwareURL.find_last_of('/') + 1);
			firmwareManager.m_uploadStatus = 10;

			if (FileDownloader().DownloadFile(firmwareURL, path + fileName))
			{
				while (firmwareManager.m_uploadStatus != 40)
				{
					firmwareManager.m_uploadStatus += 2;
					Sleep(50);
				}

				if (firmwareManager.LoadFirmware(connection, path + fileName))
				{
					firmwareManager.m_uploadStatus = 100;
					return;
				}
			}
		}
	}

	firmwareManager.m_uploadStatus = -1;
}