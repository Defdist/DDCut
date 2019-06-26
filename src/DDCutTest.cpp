#include "DDCutDaemon.h"
#include "Common/defines.h"
#include "RestClient/DDRestClient.h"
#include "RestClient/FileDownloader.h"
#include "Ghost/GhostGunnerManager.h"
#include "Ghost/GhostRegex.h"

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

	daemon.SetDDFile("P:\\Git\\Github\\DDCutMaster\\Cutting Code\\AR15 Code\\AR15_pocket+selector+pins.dd");

	daemon.SelectJob(0);
	GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();

	std::cout << "Step 0\n";
	Sleep(1000);
	daemon.StartMilling(0);

	while (true)
	{
		const auto status = daemon.GetMillingStatus(0);
		const int percentage = status.GetPercentage();
		if (percentage == 100)
		{
			break;
		}
		else if (percentage == -1)
		{
			std::cout << status.GetErrorMessage() << "\n";
			break;
			//throw std::exception("Error");
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

void TestMillingP80()
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	daemon.Initialize();

	while (daemon.GetGhostGunnerStatus() != EGhostGunnerStatus::connected)
	{
		std::cout << "Not connected\n";
		Sleep(250);
	}

	//daemon.SetSelectedGhostGunner(daemon.GetAvailableGhostGunners().front());

	daemon.SetDDFile("H:\\GhostGunner\\Cutting Code\\p80 2019.03.14.dd");

	daemon.SelectJob(0);
	GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();

	std::cout << "Step 0\n";
	Sleep(1000);
	daemon.StartMilling(0);

	while (true)
	{
		const auto status = daemon.GetMillingStatus(0);
		const int percentage = status.GetPercentage();
		if (percentage == 100)
		{
			break;
		}
		else if (percentage == -1)
		{
			std::cout << status.GetErrorMessage() << "\n";
			break;
			//throw std::exception("Error");
		}

		std::cout << std::to_string(percentage) << "\n";
		Sleep(100);
	}

	std::cout << "Step 7\n";
	Sleep(1000);
	daemon.StartMilling(7);

	while (true)
	{
		const int percentage = daemon.GetMillingStatus(7).GetPercentage();
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

	std::cout << "Step 27 - Probing\n";
	Sleep(1000);
	daemon.StartMilling(27);

	while (true)
	{
		const int percentage = daemon.GetMillingStatus(27).GetPercentage();
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

	std::cout << "Step 28\n";
	Sleep(1000);
	daemon.StartMilling(28);

	while (true)
	{
		const int percentage = daemon.GetMillingStatus(28).GetPercentage();
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
	/*DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	daemon.Initialize();

	std::unique_ptr<CustServiceReqError> pError = daemon.SendCustomerSupportRequest("Email@gmail.com", "DESCRIPTION", false);
	if (pError != nullptr)
	{
		if (pError->ERRORS.empty())
		{
			return 0;
		}
	}

	std::string line = "[G54:0.000,0.000,0.000]";
	std::smatch sm;

	if (line.compare(0, 2, "[G") == 0)
	{
		if (std::regex_match(line, sm, Ghost::Regex::RXWCS))
		{
			return -7;
		}
	}*/
	//TestMilling();
	TestMillingP80();

	//daemon.GetAvailableFirmwareUpdates();


	//std::vector<AvailableFirmware> available = DDRestClient::CheckForFirmwareUpdates("1.1.0", "2.0");
	//FileDownloader::DownloadFile(available[2].FILES[0], "P:\\Git\\Github\\DDCut\\firmware\\file.hex");

	//DDRestClient().CheckForSoftwareUpdates("1.0.1");
	//system("DDUpdater.exe 1.0.1");
	//DDUpdater().UpdateDDCut("ddcut2.exe", "1.0.1");


	return 1;
}