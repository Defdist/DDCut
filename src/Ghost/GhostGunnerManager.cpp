#include "GhostGunnerManager.h"

#include "GhostException.h"
#include "ConnectionInitializer.h"
#include "ProbeHelper.h"

#include <Settings/SettingManager.h>
#include <DDLogger/DDLogger.h>

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

	DDLogger::Log("GhostGunnerManager::SetSelectedGhostGunner() - Path: " + ghostGunner.GetPath() + " Serial Number: " + ghostGunner.GetSerialNumber());
	m_selectedGhostGunner = new GhostConnection(ghostGunner);
	return true;
}

void GhostGunnerManager::SetSelectedGhostGunner(GhostConnection* pGhostConnection)
{
	delete m_selectedGhostGunner;
	m_selectedGhostGunner = pGhostConnection;
}

bool GhostGunnerManager::IsSelectedGhostGunner(const GhostGunner& ghostGunner) const
{
	if (m_selectedGhostGunner != nullptr)
	{
		return m_selectedGhostGunner->GetGhostGunner() == ghostGunner;
	}

	return false;
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

std::unique_ptr<GhostException>  GhostGunnerManager::ReadWriteCycle(Job* pJob, Operation* pOperation, const int hardLimitCount)
{
	// Uses pOperation, ps->filesize, ps->abortJob
	try
	{
		if (pOperation != nullptr && pOperation->GetTimeout() > 0)
		{
			DDLogger::Log("GhostGunnerManager::ReadWriteCycle - Using operation timeout: " + std::to_string(pOperation->GetTimeout()));
			m_selectedGhostGunner->setTimeout(std::chrono::seconds(pOperation->GetTimeout()));
		}
		else
		{
			DDLogger::Log("GhostGunnerManager::ReadWriteCycle - Using global timeout: " + std::to_string(SettingManager::GetInstance().GetTimeout()));
			m_selectedGhostGunner->setTimeout(std::chrono::seconds(SettingManager::GetInstance().GetTimeout()));
		}

		m_selectedGhostGunner->ResetIdleTime();

		bool cleanup = true;
		while (true)
		{
			if (!m_selectedGhostGunner->WriteCache())
			{
				if (cleanup && !(m_selectedGhostGunner->getState() & Ghost::Status::GS_LOCKED))
				{
					DDLogger::Log("GhostGunnerManager::ReadWriteCycle - Cleaning up. Sending G4 P0.1");
					m_selectedGhostGunner->send("G4 P0.1"); // Wait for 0.1 seconds (http://linuxcnc.org/docs/html/gcode/g-code.html#gcode:g4)
					cleanup = false;
				}
				else
				{
					break;
				}
			}

			bool sleep = true;
			std::string s = "";
			while (m_selectedGhostGunner->ReadLine(s))
			{
				sleep = false;
				DDLogger::Log("GhostGunnerManager::ReadWriteCycle - Line read: [" + s + "]");
				s = "";
			}

			m_selectedGhostGunner->UpdateFeedRate();

			if (sleep)
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
			DDLogger::Log("GhostGunnerManager::ReadWriteCycle - Timeout exceeded.");
			return unique::make_unique<GhostException>(GhostException(GhostException::TIMEOUT));
		}
		else if (pJob != nullptr && pOperation->GetReset())
		{
			DDLogger::Log("GhostGunnerManager::ReadWriteCycle - Calling reset().");
			m_selectedGhostGunner->reset();
		}

		return std::unique_ptr<GhostException>(nullptr);
	}
	catch (GhostException& e)
	{
		std::string exceptionMessage = e.what();
		DDLogger::Log("GhostGunnerManager::ReadWriteCycle - Exception occured: " + exceptionMessage);
		DDLogger::Flush();
		if (e.getType() == GhostException::ALARM_LIMIT && (m_selectedGhostGunner->getState() & Ghost::Status::GS_HOMING))
		{
			// This mess deals with the case when someone has managed to get their machine stuck on a hard limit. It will try to unstick it 3 times.
			if (hardLimitCount >= 3)
			{
				return unique::make_unique<GhostException>(GhostException(e));
			}
			else
			{
				DDLogger::Log("Attempting to unstick from hard limits and rerunning operation");
				try
				{
					DDLogger::Log("Unsetting soft limits");
					Sleep(1000);
					HardSend("$20=0");

					DDLogger::Log("Reconnecting");
					m_selectedGhostGunner->reconnect();

					DDLogger::Log("Reconnected, unsticking");
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
					DDLogger::Log("Setting soft limits");
					Sleep(1000);
					HardSend("$20=1");

					if (e.getType() == GhostException::ALARM_LIMIT)
					{
						DDLogger::Log("Reconnecting");
						m_selectedGhostGunner->reconnect();


						DDLogger::Log("Reconnected, resending operation");
						m_selectedGhostGunner->send(pOperation->GetGCodeFile());
						return ReadWriteCycle(pJob, pOperation, hardLimitCount + 1);
					}
					else
					{
						return unique::make_unique<GhostException>(GhostException(e));
					}
				}
				catch (...)
				{
					// Set soft limits
					HardSend("$20=1");
					return unique::make_unique<GhostException>(GhostException(GhostException::GRBL_ERROR)); // TODO: Determine error
				}
			}
		}
		else
		{
			return unique::make_unique<GhostException>(GhostException(e));
		}
	}
	catch (...)
	{
		return unique::make_unique<GhostException>(GhostException(GhostException::GRBL_ERROR)); // TODO: Determine error
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