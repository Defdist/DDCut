#include "GhostGunnerManager.h"

#include "GhostException.h"
#include "ConnectionInitializer.h"
#include "ProbeHelper.h"

#include <Settings/SettingManager.h>
#include <Logging/Logger.h>

GhostGunnerManager& GhostGunnerManager::GetInstance()
{
	static GhostGunnerManager instance;
	return instance;
}

GhostConnection* GhostGunnerManager::GetConnection()
{
	return m_selectedGhostGunner;
}

bool GhostGunnerManager::SetSelectedGhostGunner(const GhostGunner& ghostGunner)
{
	delete m_selectedGhostGunner;

	Logger::GetInstance().Log("GhostGunnerManager::SetSelectedGhostGunner() - Path: " + ghostGunner.GetPath() + " Serial Number: " + ghostGunner.GetSerialNumber());
	m_selectedGhostGunner = new GhostConnection(ghostGunner);
	return true;
}

void GhostGunnerManager::SetSelectedGhostGunner(GhostConnection* pGhostConnection)
{
	delete m_selectedGhostGunner;
	m_selectedGhostGunner = pGhostConnection;
}

void GhostGunnerManager::ShutdownGhostGunner(Job* pJob, Operation* pOperation)
{
	if (m_selectedGhostGunner != nullptr && m_selectedGhostGunner->IsConnected())
	{
		if (m_selectedGhostGunner->getState() & Ghost::Status::GS_SPINDLE)
		{
			// TODO: Use HardSend instead of send & ReadWriteCycle?
			m_selectedGhostGunner->send("S0 (Stopping spindle)");
			m_selectedGhostGunner->send("M5 (Stopping spindle)");
			ReadWriteCycle(pJob, pOperation, 0);
		}

		// $X (Kill Alarm Clock) will override the locks and allow G-code functions to work again.
		m_selectedGhostGunner->send("$X");

		ReadWriteCycle(pJob, pOperation, 0);

		m_selectedGhostGunner->reset();
		m_selectedGhostGunner->disconnect();
	}
}

bool GhostGunnerManager::ReadWriteCycle(Job* pJob, Operation* pOperation, const int hardLimitCount)
{
	// Uses pOperation, ps->filesize, ps->abortJob
	try
	{
		bool hit, cleanup = true;
		std::string s;

		if (pOperation != nullptr && pOperation->GetTimeout() > 0)
		{
			Logger::GetInstance().Log("GhostGunnerManager::ReadWriteCycle - Using operation timeout: " + std::to_string(pOperation->GetTimeout()));
			m_selectedGhostGunner->setTimeout(std::chrono::seconds(pOperation->GetTimeout()));
		}
		else
		{
			Logger::GetInstance().Log("GhostGunnerManager::ReadWriteCycle - Using global timeout: " + std::to_string(SettingManager::GetInstance().GetTimeout()));
			m_selectedGhostGunner->setTimeout(std::chrono::seconds(SettingManager::GetInstance().GetTimeout()));
		}

		m_selectedGhostGunner->ResetIdleTime();

		while (true)
		{
			if (!m_selectedGhostGunner->WriteCache())
			{
				if (cleanup && !(m_selectedGhostGunner->getState() & Ghost::Status::GS_LOCKED))
				{
					Logger::GetInstance().Log("GhostGunnerManager::ReadWriteCycle - Cleaning up. Sending G4 P0.1");
					m_selectedGhostGunner->send("G4 P0.1"); // Wait for 0.1 seconds (http://linuxcnc.org/docs/html/gcode/g-code.html#gcode:g4)
					cleanup = false;
				}
				else
				{
					break;
				}
			}

			hit = false;
			while (m_selectedGhostGunner->ReadLine(s))
			{
				hit = true;
				Logger::GetInstance().Log("GhostGunnerManager::ReadWriteCycle - Line read: [" + s + "]");
			}

			m_selectedGhostGunner->UpdateFeedRate();

			if (!hit)
			{
				Sleep(10);
			}

			if (m_selectedGhostGunner->getState() & Ghost::Status::GS_TIMEOUT)
			{
				break;
			}
		}

		if (m_selectedGhostGunner->getState() & Ghost::Status::GS_TIMEOUT)
		{
			Logger::GetInstance().Log("GhostGunnerManager::ReadWriteCycle - Timeout exceeded.");
			return false;
		}
		else
		{
			if (pJob != nullptr && pOperation->GetReset())
			{
				Logger::GetInstance().Log("GhostGunnerManager::ReadWriteCycle - Calling reset().");
				m_selectedGhostGunner->reset();
			}

			return true;
		}

	}
	catch (GhostException& e)
	{
		std::string exceptionMessage = e.what();
		Logger::GetInstance().Log("GhostGunnerManager::ReadWriteCycle - Exception occured: " + exceptionMessage);
		if (e.getType() == GhostException::ALARM_LIMIT && (m_selectedGhostGunner->getState() & Ghost::Status::GS_HOMING))
		{
			// This mess deals with the case when someone has managed to get their machine stuck on a hard limit. It will try to unstick it 3 times.
			if (hardLimitCount >= 3)
			{
				return false;
			}
			else
			{
				Logger::GetInstance().Log("Attempting to unstick from hard limits and rerunning operation");
				try
				{
					Logger::GetInstance().Log("Unsetting soft limits");
					Sleep(1000);
					HardSend("$20=0");

					Logger::GetInstance().Log("Reconnecting");
					m_selectedGhostGunner->reconnect();

					Logger::GetInstance().Log("Reconnected, unsticking");
					m_selectedGhostGunner->send("$X");
					m_selectedGhostGunner->send("G91");
					m_selectedGhostGunner->send("G1 X1 Y-1 Z-1 F10");
					m_selectedGhostGunner->send("G4 P0.1"); // Wait for 0.1 seconds (http://linuxcnc.org/docs/html/gcode/g-code.html#gcode:g4)

					std::string buffer;
					while (m_selectedGhostGunner->WriteCache())
					{
						m_selectedGhostGunner->ReadLine(buffer);
					}

					throw GhostException(GhostException::ALARM_LIMIT);
				}
				catch (GhostException& e)
				{
					Logger::GetInstance().Log("Setting soft limits");
					Sleep(1000);
					HardSend("$20=1");

					if (e.getType() == GhostException::ALARM_LIMIT)
					{
						Logger::GetInstance().Log("Reconnecting");
						m_selectedGhostGunner->reconnect();


						Logger::GetInstance().Log("Reconnected, resending operation");
						m_selectedGhostGunner->send(pOperation->GetGCodeFile());
						return ReadWriteCycle(pJob, pOperation, hardLimitCount + 1);
					}
					else
					{
						return false;
					}
				}
				catch (std::exception& e)
				{
					// Set soft limits
					HardSend("$20=1");
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
	catch (std::exception& e)
	{
		return false;
	}
}

void GhostGunnerManager::HardSend(const std::string& command)
{
	std::string buffer;
	m_selectedGhostGunner->reset();
	m_selectedGhostGunner->send(command);
	while (m_selectedGhostGunner->WriteCache())
	{
		m_selectedGhostGunner->ReadLine(buffer);
	}
}