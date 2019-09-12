#include "ConnectionInitializer.h"

#include "GhostConnection.h"
#include "GhostGunnerManager.h"
#include "DDLogger/DDLogger.h"

bool ConnectionInitializer::InitializeConnection(GhostConnection& ghostConnection) const
{
	try
	{
		DDLogger::Log("ConnectionInitializer::InitializeConnection() - Connecting to ghost...");
		ghostConnection.connect();

		WaitForStartup(ghostConnection);
		ghostConnection.WriteWithTimeout("$X\n", 100); // TODO: Unlock it.
		Sleep(500);
		HandleFirmwareUpgrade(ghostConnection);

        DDLogger::Log("ConnectionInitializer::InitializeConnection() - Success");
		return true;
	}
	catch (std::exception& e)
	{
		DDLogger::Log("ConnectionInitializer::InitializeConnection() - Connect Failed: " + std::string(e.what()));
		return false;
	}
}

void ConnectionInitializer::WaitForStartup(GhostConnection& ghostConnection) const
{
	const std::chrono::system_clock::time_point lastReadTime = std::chrono::system_clock::now();
	const std::chrono::seconds timeout = std::chrono::seconds(5);

	ghostConnection.flushReads();

	while (true)
	{
		try
		{
			std::string s;
			if (ghostConnection.ReadLine(s))
			{
				DDLogger::Log("ConnectionInitializer::WaitForStartup() - Line read: " + s);
			}
			else if (!(ghostConnection.getState() & Ghost::Status::GS_STARTUP))
			{
				break;
			}
			else
			{
				auto delta = std::chrono::system_clock::now() - lastReadTime;
				if (delta > timeout)
				{
					DDLogger::Log("ConnectionInitializer::WaitForStartup() - Connection timeout");
					ghostConnection.reset();
				}

				Sleep(50);
			}
		}
		catch (std::exception& e)
		{
			DDLogger::Log("ConnectionInitializer::WaitForStartup() - Exception: " + std::string(e.what()));
			ghostConnection.reset();
			// TODO: Why are we catching this exception?
		}
	}
}

void ConnectionInitializer::HandleFirmwareUpgrade(GhostConnection& ghostConnection) const
{
	//const FirmwareVersion firmwareVersion = GhostFirmwareManager::GetInstance().GetFirmwareVersion(ghostConnection);
	//DDLogger::Log("ConnectionInitializer::HandleFirmwareUpgrade() - Firmware Version: [" + firmwareVersion.grblVersion + ", " + firmwareVersion.ddVersion + "]");

	//if (SettingManager::GetInstance().GetHexLoad())
	//{
	//	const std::string resetResponse = ghostConnection.ResetGGVars();
	//	DDLogger::Log("ConnectionInitializer::HandleFirmwareUpgrade() - " + resetResponse);

	//	SettingManager::GetInstance().SetHexLoad(false);
	//}
}
