#include "ConnectionInitializer.h"

#include "GhostConnection.h"
#include "GhostGunnerManager.h"
#include "Logging/Logger.h"

bool ConnectionInitializer::InitializeConnection(GhostConnection& ghostConnection) const
{
	try
	{
		Logger::GetInstance().Log("ConnectionInitializer::InitializeConnection() - Connecting to ghost...");
		ghostConnection.connect();

		WaitForStartup(ghostConnection);
		ghostConnection.WriteWithTimeout("$X\n", 100); // TODO: Unlock it.
		Sleep(500);
		HandleFirmwareUpgrade(ghostConnection);

        Logger::GetInstance().Log("ConnectionInitializer::InitializeConnection() - Success");
		return true;
	}
	catch (std::exception& e)
	{
		Logger::GetInstance().Log("ConnectionInitializer::InitializeConnection() - Connect Failed: " + std::string(e.what()));
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
				Logger::GetInstance().Log("ConnectionInitializer::WaitForStartup() - Line read: " + s);
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
					Logger::GetInstance().Log("ConnectionInitializer::WaitForStartup() - Connection timeout");
					ghostConnection.reset();
				}

				Sleep(50);
			}
		}
		catch (std::exception& e)
		{
			Logger::GetInstance().Log("ConnectionInitializer::WaitForStartup() - Exception: " + std::string(e.what()));
			ghostConnection.reset();
			// TODO: Why are we catching this exception?
		}
	}
}

void ConnectionInitializer::HandleFirmwareUpgrade(GhostConnection& ghostConnection) const
{
	//const FirmwareVersion firmwareVersion = GhostFirmwareManager::GetInstance().GetFirmwareVersion(ghostConnection);
	//Logger::GetInstance().Log("ConnectionInitializer::HandleFirmwareUpgrade() - Firmware Version: [" + firmwareVersion.grblVersion + ", " + firmwareVersion.ddVersion + "]");

	//if (SettingManager::GetInstance().GetHexLoad())
	//{
	//	const std::string resetResponse = ghostConnection.ResetGGVars();
	//	Logger::GetInstance().Log("ConnectionInitializer::HandleFirmwareUpgrade() - " + resetResponse);

	//	SettingManager::GetInstance().SetHexLoad(false);
	//}
}
