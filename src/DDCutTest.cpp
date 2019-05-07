#include "DDCutDaemon.h"
#include "Common/defines.h"
#include "RestClient/DDRestClient.h"
#include "RestClient/FileDownloader.h"
#include "DDUpdater/DDUpdater.h"
#include "Ghost/GhostGunnerManager.h"

#include <iostream>

void TestMilling()
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	daemon.Initialize();

	while (daemon.GetGhostGunnerStatus() != EGhostGunnerStatus::connected)
	{
		std::cout << "Not connected\n";
		Sleep(250);
	}

	//daemon.SetSelectedGhostGunner(daemon.GetAvailableGhostGunners().front());

	daemon.SetDDFile("P:\\Git\\Github\\DDCut\\Cutting Code\\AR15 Code\\AR15-pocket+selector+pins.dd");

	daemon.SelectJob(0);
	GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();

	std::cout << "Step 0\n";
	Sleep(1000);
	daemon.StartMilling(0);

	while (true)
	{
		const int percentage = daemon.GetMillingStatus(0).GetPercentage();
		if (percentage == 100)
		{
			break;
		}
		else if (percentage == -1)
		{
			throw std::exception("Error");
		}

		std::cout << std::to_string(percentage) << "\n";
		Sleep(100);
	}

	std::cout << "Step 19\n";
	Sleep(1000);
	daemon.StartMilling(19);

	while (true)
	{
		const int percentage = daemon.GetMillingStatus(19).GetPercentage();
		if (percentage == 100)
		{
			break;
		}
		else if (percentage == -1)
		{
			throw std::exception("Error");
		}

		std::cout << std::to_string(percentage) << "\n";
		Sleep(100);
	}

	std::cout << "Step 24\n";
	Sleep(1000);
	daemon.StartMilling(24);

	while (true)
	{
		const int percentage = daemon.GetMillingStatus(24).GetPercentage();
		if (percentage == 100)
		{
			break;
		}
		else if (percentage == -1)
		{
			throw std::exception("Error");
		}

		std::cout << std::to_string(percentage) << "\n";
		Sleep(100);
	}

	std::cout << "Step 25\n";
	Sleep(1000);
	daemon.StartMilling(25);

	while (true)
	{
		const int percentage = daemon.GetMillingStatus(25).GetPercentage();
		if (percentage == 100)
		{
			break;
		}
		else if (percentage == -1)
		{
			throw std::exception("Error");
		}

		std::cout << std::to_string(percentage) << "\n";
		Sleep(100);
	}

	std::cout << "Step 26\n";
	Sleep(1000);
	daemon.StartMilling(26);

	while (true)
	{
		const int percentage = daemon.GetMillingStatus(26).GetPercentage();
		if (percentage == 100)
		{
			break;
		}
		else if (percentage == -1)
		{
			throw std::exception("Error");
		}

		std::cout << std::to_string(percentage) << "\n";
		Sleep(100);
	}

	daemon.Shutdown();
}

int main(int argc, char* argv[])
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	daemon.Initialize();

	std::unique_ptr<CustServiceReqError> pError = daemon.SendCustomerSupportRequest("Email", "", false);
	if (pError != nullptr)
	{
		if (pError->ERRORS.empty())
		{
			return 0;
		}
	}

	//TestMilling();

	//daemon.GetAvailableFirmwareUpdates();


	//std::vector<AvailableFirmware> available = DDRestClient::CheckForFirmwareUpdates("1.1.0", "2.0");
	//FileDownloader::DownloadFile(available[2].FILES[0], "P:\\Git\\Github\\DDCut\\firmware\\file.hex");

	//DDRestClient().CheckForSoftwareUpdates("1.0.1");
	//system("DDUpdater.exe 1.0.1");
	//DDUpdater().UpdateDDCut("ddcut2.exe", "1.0.1");


	return 1;
}