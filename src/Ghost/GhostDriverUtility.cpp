#include "GhostDriverUtility.h"

#include "DDLogger/DDLogger.h"
#include "Common/OSUtility.h"

#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <setupapi.h>
#endif

#define INFO_BUFFER_SIZE 32767

// TODO: Does it even matter if the driver is installed?
bool GhostDriverUtility::IsArduinoDriverInstalled() const
{
	bool result = false;

#ifdef _WIN32
	HDEVINFO hdevinfo;

	bool found = false;

	std::vector<std::string> vec;
	vec.push_back("usb\\vid_2341&pid_0043");
	vec.push_back("usb\\vid_2341&PID_0001");

	for (const std::string dr : vec)
	{
		hdevinfo = SetupDiGetClassDevs(NULL, dr.c_str(), NULL, DIGCF_ALLCLASSES);

		if (hdevinfo == INVALID_HANDLE_VALUE)
		{
			DWORD err = GetLastError();
			DDLogger::Log("GhostDriverUtility::IsArduinoDriverInstalled() - Not Found: " + std::to_string(err));
		}
		else
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		return false;
	}

	char  instance_id[4096];
	SP_DEVINFO_DATA devinfo;

	for (DWORD n = 0;; n++)
	{
		devinfo.cbSize = sizeof(devinfo);
		if (!SetupDiEnumDeviceInfo(hdevinfo, n, &devinfo))
		{
			break;
		}
		if (!SetupDiGetDeviceInstanceId(hdevinfo, &devinfo, instance_id, _countof(instance_id), NULL))
		{
			DWORD err = GetLastError();
			DDLogger::Log("GhostDriverUtility::IsArduinoDriverInstalled() - SetupDiGetDeviceInstanceId: " + std::to_string(err));
		}
		else
		{
			LPTSTR buffer = NULL;
			DWORD buffersize = 0;
			DWORD DataT;

			//cout << "DevicePath: " <<  instance_id << endl;
			while (!SetupDiGetDeviceRegistryProperty(hdevinfo, &devinfo, SPDRP_DEVICEDESC, &DataT, (PBYTE)buffer, buffersize, &buffersize))
			{
				if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				{
					// Change the buffer size.
					if (buffer) LocalFree(buffer);
					buffer = (LPSTR)LocalAlloc(LPTR, buffersize * 2); // ERROR LINE
				}
				else
				{
					// Insert error handling here.
					break;
				}
			}

			if (buffer)
			{
				LocalFree(buffer);
			}

			result = true;
		}
	}

	SetupDiDestroyDeviceInfoList(hdevinfo);
#endif
	return result;
}

// A driver is not necessary for MacOS X, since it ships with a generic serial driver for USB.
bool GhostDriverUtility::InstallHardwareDriver() const
{
#ifdef _WIN32
	// 1. Get system directory
	TCHAR  infoBuf[INFO_BUFFER_SIZE];
	GetSystemDirectory(infoBuf, INFO_BUFFER_SIZE);
	std::string sysdir = infoBuf;

	// 2. Determine arduino directory
	std::string newDir = OSUtility::GetExecPath() + "\\Drivers\\Arduino";
	DDLogger::Log("GhostDriverUtility::InstallHardwareDriver - Arduino directory: " + newDir);

	// 3. Build command
	const std::string command = sysdir + "\\cmd.EXE /C install.bat";

	// 4. Execute command in new process
	if (!OSUtility::ExecuteCommandInNewProcess(command, newDir))
	{
		DDLogger::Log("GhostDriverUtility::InstallHardwareDriver - Failure: " + std::to_string(GetLastError()));
		return false;
	}

	DDLogger::Log("GhostDriverUtility::InstallHardwareDriver - Success");

	MessageBox(NULL, "The Ardiuno Device Driver was loaded; Please unplug GhostGunner from USB and plug it back in to activate the port.", "Information", MB_ICONINFORMATION | MB_OK);
#endif
	
	return true;
}