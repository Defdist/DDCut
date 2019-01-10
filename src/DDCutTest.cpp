#include "DDCutDaemon.h"
#include "Common/defines.h"
#include "RestClient/DDRestClient.h"
#include "RestClient/FileDownloader.h"
#include "DDUpdater/DDUpdater.h"

#include <iostream>

int main(int argc, char* argv[])
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	daemon.Initialize();

	while (daemon.GetGhostGunnerStatus() != EGhostGunnerStatus::connected)
	{
		std::cout << "Not connected\n";
		Sleep(100);
	}

	daemon.GetAvailableFirmwareUpdates();


	std::vector<AvailableFirmware> available = DDRestClient::CheckForFirmwareUpdates("1.1.0", "2.0");
	FileDownloader::DownloadFile(available[2].FILES[0], "P:\\Git\\Github\\DDCut\\firmware\\file.hex");



	//DDRestClient().CheckForSoftwareUpdates("1.0.1");
	//system("DDUpdater.exe 1.0.1");

	return 1;
}