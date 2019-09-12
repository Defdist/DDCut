#ifdef _WIN32
#include "GhostGunnerFinder.h"

#include "GhostException.h"
#include <DDLogger/DDLogger.h>

#include <regex>
#include <windows.h>
#include <initguid.h>
#include <winioctl.h>
#include <setupapi.h>

/*std::list<std::string> GhostGunnerFinder::GetAvailableGhostGunnersWithoutDriver() const
{
std::list<std::string> availableGhostGunners;

// Driver less code to detect ghost gunner
std::string szClass = "USB";

HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, szClass.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
if( INVALID_HANDLE_VALUE == hDevInfo ) {
return std::list<std::string>();
}

SP_DEVINFO_DATA spDevInfoData;
spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

SP_INTERFACE_DEVICE_DATA Interface_Info;
Interface_Info.cbSize = sizeof(Interface_Info);

for (int i=0; SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
{
DWORD nSize=0 ;
TCHAR buf[MAX_PATH];

DWORD DataT;
LPTSTR buffer = NULL;
DWORD buffersize = 0;


if (!SetupDiGetDeviceInstanceId(hDevInfo, &spDevInfoData, buf, sizeof(buf), &nSize))
{
fprintf(stderr, "SetupDiGetDeviceInstanceId() error");
continue;
}

std::string devicename(buf);
//std::cout << devicename << endl;
if ((devicename.find("USB\\VID_2341&PID_0043") == std::string::npos) && (devicename.find("USB\\VID_1A86&PID_7523") == std::string::npos))
{
continue;
}

// found Cube, lookup registry properties
while (!SetupDiGetDeviceRegistryProperty(
hDevInfo,
&spDevInfoData,
SPDRP_FRIENDLYNAME, // SPDRP_DEVICEDESC
&DataT,
(PBYTE)buffer,
buffersize,
&buffersize))
{

if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
{
// Change the buffer size.
if (buffer) LocalFree(buffer);
// Double the size to avoid problems on
// W2k MBCS systems per KB 888609.
buffer = (LPTSTR)LocalAlloc(LPTR,buffersize * 2);


}
else
{
// Insert error handling here.
break;
}
}
//std::cout << devicename << endl;
//std::cout << buffer << endl;
std::string tmp(buffer);
std::string device(tmp.begin() + tmp.find_first_of("(")+1, tmp.begin() + tmp.find_last_of(")"));

availableGhostGunners.push_back(device);

if (buffer)
{
LocalFree(buffer);
}
}

// cleanup
SetupDiDestroyDeviceInfoList(hDevInfo);

return availableGhostGunners;
}*/

std::list<GhostGunner> GhostGunnerFinder::GetAvailableGhostGunners() const
{
	std::list<GhostGunner> availableGhostGunners;

	const HDEVINFO hdi = SetupDiGetClassDevs(&GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR, NULL, NULL, DIGCF_PRESENT);
	if (hdi != INVALID_HANDLE_VALUE)
	{
		SP_DEVINFO_DATA spdid;
		spdid.cbSize = sizeof(SP_DEVINFO_DATA);

		int i = 0;
		while (true)
		{
			if (!SetupDiEnumDeviceInfo(hdi, i, &spdid))
			{
				const DWORD err = GetLastError();
				if (err == ERROR_NO_MORE_ITEMS)
				{
					break;
				}
				else
				{
					throw GhostException(GhostException::NO_ACCESS, std::to_string(err));
				}
			}
			else
			{
				CHAR nameBuf[MAX_PATH];
				CHAR serialBuf[MAX_PATH];
				DWORD valueType;
				DWORD valueSize;
				if (SetupDiGetDeviceRegistryProperty(hdi, &spdid, SPDRP_FRIENDLYNAME, &valueType, (PBYTE)nameBuf, MAX_PATH, &valueSize)
					&& SetupDiGetDeviceInstanceId(hdi, &spdid, serialBuf, MAX_PATH, &valueSize))// SetupDiGetDeviceRegistryProperty(hdi, &spdid, SPDRP_HARDWAREID, &valueType, (PBYTE)serialBuf, MAX_PATH, &valueSize))
				{
					const std::string nameStr = nameBuf;
					const std::string serialNumber = serialBuf;
					const std::string formattedSerialNumber = serialNumber.substr(serialNumber.find_last_of('\\') + 1);

					std::smatch sm;
					const std::regex RXARDUINO("^Arduino Uno \\((.*)\\)$");
					if (std::regex_match(nameStr, sm, RXARDUINO))
					{
						const std::string path = "\\\\.\\" + sm[1].str();
						//DDLogger::Log("GhostGunnerFinder::GetAvailableGhostGunners() - Arduino Found: " + nameStr + " Path: " + path + " Serial Number: " + formattedSerialNumber);
                        availableGhostGunners.push_back(GhostGunner(path, formattedSerialNumber));
					}
				}
				else
				{
					const DWORD err = GetLastError();
					throw GhostException(GhostException::NO_ACCESS, std::to_string(err));
				}
			}

			++i;
		}
	}

	return availableGhostGunners;
}

#endif
