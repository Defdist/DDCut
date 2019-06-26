#include "GhostConnection.h"

#include "GhostFirmwareManager.h"
#include "GhostRegex.h"
#include "Common/OSUtility.h"
#include "M100.h"
#include "M101.h"
#include "DDLogger/DDLogger.h"
#include "Common/LockUtility.h"
#include "Display/GhostDisplayManager.h"

#include <iostream>
#include <sstream>
#include <ios>

// TODO: Remove the using namespaces
using namespace Ghost;
using namespace Ghost::Regex;
using namespace Ghost::Status;

GhostConnection::GhostConnection(const GhostGunner& ghostGunner)
	: m_ghostGunner(ghostGunner)
{
	m_ghSemaphore = LockUtility::CreateLock();
	if (m_ghSemaphore == NULL)
	{
		DDLogger::Log("GhostConnection::GhostConnection() - ********** semaphore is null **********");
	}
}

void GhostConnection::CleanState()
{
    while (!m_readCache.empty())
	{
		m_readCache.pop();
	}

	m_readBuffer = "";
	m_lastReadTime = std::chrono::system_clock::now();
	m_timeout = std::chrono::seconds(580);

    while (!m_dqWriteBuffer.empty())
	{
		m_dqWriteBuffer.pop_front();
	}

    while (!m_currentWrites.empty())
	{
		m_currentWrites.pop();
	}

	m_currentWrites.clear();
	m_lastGGroup = -1;
	m_state = 0;
}

void GhostConnection::SetGGParms()
{
	// Set reporting features to report in millimeters
	WriteWithTimeout("$13=0\n", 100);

	flushReads();
}

void GhostConnection::connect()
{
	if (m_ghostGunner.GetPath().length() == 0)
	{
		throw GhostException(GhostException::FAILED_OPEN, "Path Empty");
	}

	CleanState();
	connectOS();
	m_state = GS_CONNECTED|GS_STARTUP|GS_BOOTING;
}

void GhostConnection::disconnect()
{
	VerifyConnected();

	CleanState();
	disconnectOS();
}

void GhostConnection::reset()
{
	VerifyConnected();

	char t=24;
	if (!OSUtility::WriteToFile(m_file, &t, 1))
	{
		throw GhostException(GhostException::FAILED_WRITE);
	}

	Sleep(1000);
	flushReads();
	CleanState();
	m_state = GS_CONNECTED;
}

//std::string GhostConnection::ResetGGVars()
//{
//	// This clears and restores all of the EEPROM data used by Grbl.
//	// This includes $$ settings, $# parameters, $N startup lines, and $I build info string. 
//	WriteWithTimeout("$RST=*\n", 1000);
//
//	return ReadLineAndFlush();
//}

void GhostConnection::reconnect()
{
	VerifyConnected();

    disconnect();
    connect();

	if (!IsConnected())
	{
		throw GhostException(GhostException::FAILED_OPEN, "Reconnect failed");
	}

    while(true)
	{
		std::string s;
        if (ReadLine(s))
		{
        }
		else if (!(getState() & GS_STARTUP))
		{
            break;
        }
		else
		{
            Sleep(50);
        }
    }
}

void GhostConnection::VerifyConnected() const
{
	if (!IsConnected())
	{
        throw GhostException(GhostException::NOT_OPEN);
	}
}

unsigned int GhostConnection::getState()
{
    const std::chrono::system_clock::duration delta = std::chrono::system_clock::now() - m_lastReadTime;
    if (!(m_state & GS_TIMEOUT))
	{
        if (delta > m_timeout)
		{
			m_state |= GS_TIMEOUT;
        }
		else if ((m_state & GS_STARTUP) && !(m_state & GS_BOOTING) && (delta > STARTDELAY))
		{
			m_state &= ~GS_STARTUP;
        }
    }

    return m_state;
}

void GhostConnection::ResetIdleTime()
{
	m_lastReadTime = std::chrono::system_clock::now();
	m_state &= ~GS_TIMEOUT;
}

void GhostConnection::ClearProbeStatus()
{
	m_state &= ~GS_LOCKED;
	m_state &= ~GS_ERROR;
}

//////////////////////////////////////////////////////
// Send - Adds GCode lines to the write buffer.
//////////////////////////////////////////////////////

void GhostConnection::send(const std::vector<std::string>& vs)
{
	VerifyConnected();

    for (size_t i = 0; i < vs.size(); ++i)
	{
		//DDLogger::Log("GhostConnection::send() - Sending: " + vs[i]);
        m_dqWriteBuffer.push_back(GCodeLine(vs[i]));
    }
}

void GhostConnection::send(const std::string& s)
{
	send(GCodeLine(s));
}

void GhostConnection::send(const GCodeLine& l)
{
	VerifyConnected();

	//DDLogger::Log("GhostConnection::send() - Sending: " + l.GetOriginal());
	m_dqWriteBuffer.push_back(l);
}

void GhostConnection::send(const std::vector<GCodeLine>& vg)
{
	VerifyConnected();

    for (size_t i = 0; i < vg.size(); ++i)
	{
		//DDLogger::Log("GhostConnection::send() - Sending: " + vg[i].GetOriginal());
        m_dqWriteBuffer.push_back(vg[i]);
    }
}

void GhostConnection::send(const GCodeFile& f)
{
	send(f.getLines());
}

//////////////////////////////////////////////////////
// Coordinates
//////////////////////////////////////////////////////

void GhostConnection::clearCoordinates()
{
    for (size_t i = 0; i < m_machinePosition.size(); ++i)
	{
		m_machinePosition.pop_back();
    }

	m_machinePosition.clear();
}

float GhostConnection::getXCoordinate(int idx)
{
    if (m_machinePosition.size() < 1)
	{
        throw GhostException(GhostException::NO_PROBE_COORD);
    }

    return m_machinePosition[idx].X_absolute_prior_to_probe;
}

float GhostConnection::getYCoordinate(int idx)
{
    if (m_machinePosition.size() < 1)
	{
       throw GhostException(GhostException::NO_PROBE_COORD);
    }

    return m_machinePosition[idx].Y_absolute_prior_to_probe;
}

float GhostConnection::getZCoordinate(int idx)
{
    if (m_machinePosition.size() < 1)
	{
        throw GhostException(GhostException::NO_PROBE_COORD);
    }

    return m_machinePosition[idx].Z_absolute_prior_to_probe;
}

std::map<std::string, Point3> GhostConnection::GetPoints() const
{
	std::map<std::string, Point3> pointsByGCode;

	// Request X, Y, & Z positions from the GhostGunner.
	WriteWithTimeout("$#\n", 100);

	std::string line = "";
	while (ReadSingleLine(line))
	{
		if (line.compare(0, 2, "[G") == 0)
		{
			std::smatch sm;
			if (std::regex_match(line, sm, Ghost::Regex::RXWCS))
			{
				const std::string gCode = sm[1].str();
				const std::string xValueStr = sm[2].str();
				const std::string yValueStr = sm[3].str();
				const std::string zValueStr = sm[4].str();
				DDLogger::Log("GhostConnection::GetPoints() - " + gCode + " : " + xValueStr + ", " + yValueStr + ", " + zValueStr);

				const Point3 point(gCode, std::stof(xValueStr), std::stof(yValueStr), std::stof(zValueStr));
				pointsByGCode[gCode] = point;
			}
		}
	}
	
	return pointsByGCode;
}

//////////////////////////////////////////////////////
// Read
//////////////////////////////////////////////////////

bool GhostConnection::ReadLine(std::string& buffer)
{
	VerifyConnected();

	//std::string readBuffer = "";
	//m_readBuffer = "";
	char t;
	while (OSUtility::ReadFromFile(m_file, &t, 1) > 0)
	{
        ResetIdleTime();

		if (t == '\n')
		{
			GhostDisplayManager::AddLine(ELineType::READ, m_readBuffer);

			ProcessReadLine(m_readBuffer);
			m_readBuffer = "";
		}
		else if (t != '\r')
		{
			m_readBuffer.push_back(t);
		}
	}

	if (!m_readCache.empty())
	{
		buffer = m_readCache.front();
		m_readCache.pop();
		return true;
	}

	return false;
}

void GhostConnection::ProcessReadLine(const std::string& line)
{
	m_readCache.push(line);

	std::smatch sm;
	const std::regex mStatus = RXSTATUS;

	if (std::regex_match(line, sm, RXOK))
	{
		if (m_currentWrites.total() > 0)
		{
			m_currentWrites.pop();
			if (m_state & GS_BLOCKING)
			{
				DDLogger::Log("GhostConnection::ProcessReadLine - m_currentWrites.size() = " + std::to_string(m_currentWrites.size()));
			}

			if (m_state & GS_BLOCKING && m_currentWrites.size() == 0)
			{
				DDLogger::Log("GhostConnection::ProcessReadLine - Unblocking");
				m_state &= ~GS_BLOCKING;
			}
		}
	}
	else if (std::regex_match(line, RXENABLED) || std::regex_match(line, RXDISABLED))
	{
		m_state &= ~GS_CHK_MODE;
	}
	else if (std::regex_match(line, RXSTART))
	{
		m_state &= ~GS_BOOTING;
	}
	else if (std::regex_match(line, RXLOCKED))
	{
		DDLogger::Log("GhostConnection::ReadLine() - Locked Received: " + line);
		m_state |= GS_LOCKED;
	}
	else if (std::regex_match(line, sm, RXPRB) && !(m_state & GS_WCS_M101))
	{
		//points.push_back(Point3(stof(sm[1].str()),stof(sm[2].str()),stof(sm[3].str())));
	}
	else if (std::regex_match(line, sm, mStatus))
	{
		// JT probe detection change
		m_state &= ~GS_STATUS;

		DDLogger::Log("GhostConnection::ReadLine() - Setting coordinates to: {" + sm[3].str() + ", " + sm[4].str() + ", " + sm[5].str() + "}");
		m_machinePosition.push_back(Coordinate(stof(sm[3].str()), stof(sm[4].str()), stof(sm[5].str())));

		m_state &= ~GS_STATUS_IGNORE;
	}
	else if (std::regex_match(line, sm, RXERROR))
	{
		if (m_flags & ERROR_EXCEPTION_ON)
		{
			DDLogger::Log("GhostConnection::ReadLine() - Error Received: " + line);

			m_state |= GS_ERROR;
			m_err = line;
			throw GhostException(GhostException::GRBL_ERROR, line);
		}
		else if (m_currentWrites.total() > 0)
		{
			if (!std::regex_match(sm[1].str(), RXOVERFLOW))
			{
				m_currentWrites.pop();
			}
		}
	}
	else if (std::regex_match(line, sm, RXALARM))
	{
		m_err = "Alarm: " + std::string(sm[1]);
		DDLogger::Log("GhostConnection::ReadLine() - Alarm: " + std::string(sm[1]));

		m_state |= GS_ERROR | GS_LOCKED;
		if (sm[1] == "Probe fail")
		{
			flushReads();
			while (!m_dqWriteBuffer.empty())
			{
				m_dqWriteBuffer.pop_front();
			}

			while (!m_currentWrites.empty())
			{
				m_currentWrites.pop();
			}

			throw GhostException(GhostException::ALARM_PROBE);
		}
		else if (sm[1] == "Hard/soft limit")
		{
			throw GhostException(GhostException::ALARM_LIMIT);
		}
		else
		{
			throw GhostException(GhostException::ALARM);
		}
	}

	if (m_state & GS_WCS_M101)
	{
		m_state &= ~GS_WCS_M101;
	}
}

void GhostConnection::flushReads() const
{
	VerifyConnected();

	char t;
	std::string line = "";
	while (OSUtility::ReadFromFile(m_file, &t, 1) > 0)
	{
		if (t == '\n')
		{
			DDLogger::Log("GhostConnection::FlushReads() - " + line);
			line = "";
		}
		else if (t != '\r')
		{
			line.push_back(t);
		}
	}
}

bool GhostConnection::ReadSingleLine(std::string& line) const
{
	line = "";

	char t;
	while (OSUtility::ReadFromFile(m_file, &t, 1) > 0)
	{
		if (t == '\n')
		{
			DDLogger::Log("GhostConnection::ReadSingleLine() - Line Read: " + line);
			return true;
		}
		else if (t != '\r')
		{
			line.push_back(t);
		}
	}

	return false;
}

std::string GhostConnection::ReadLineAndFlush() const
{
	VerifyConnected();

	std::string output;
	const bool lineWasRead = ReadSingleLine(output);
	if (lineWasRead)
	{
		flushReads();
	}
	else
	{
		DDLogger::Log("GhostConnection::ReadLineAndFlush() - No lines were read.");
	}

	return output;
}

//////////////////////////////////////////////////////
// Write
//////////////////////////////////////////////////////

bool GhostConnection::WriteCache()
{
	VerifyConnected();

	std::string output = "";

	while (m_dqWriteBuffer.size() > 0)
	{
	    if (m_state & GS_BLOCKING)
		{
            break;
        }

		// TODO: This lock was added for testing purposes.
		//if (LockUtility::ObtainLock(m_ghSemaphore))
		{
			const bool continueWriting = WriteNextLineInCache(output);
			//LockUtility::ReleaseLock(m_ghSemaphore);
			if (!continueWriting)
			{
				break;
			}
		}
	}

	const unsigned long outputLength = output.length();
	if (outputLength > 0)
	{
        if (m_state & GS_CHK_MODE)
		{
            Sleep(500);
        }

        if (LockUtility::ObtainLock(m_ghSemaphore))
		{
			GhostDisplayManager::AddLine(ELineType::WRITE, output);
			DDLogger::Log("GhostConnection::WriteCache() - Writing: " + output);
            if (!OSUtility::WriteToFile(m_file, output.c_str(), outputLength))
			{
				throw GhostException(GhostException::FAILED_WRITE);
			}

			LockUtility::ReleaseLock(m_ghSemaphore);
        }

        if (m_state & GS_STATUS)
		{
            Sleep(200);
        }
	}

	return m_currentWrites.size() > 0 || m_dqWriteBuffer.size() > 0;
}

bool GhostConnection::WriteNextLineInCache(std::string& output)
{
	const GCodeLine& line = m_dqWriteBuffer.front();

	if (line.GetType() == GCodeLine::TYPE_UNKNOWN || line.GetGroup() == GCodeLine::GROUP_UNKNOWN)
	{
		throw GhostException(GhostException::UNKNOWN_COMMAND, line.GetOriginal());
	}

	if (line.GetBlocking() == GCodeLine::TYPE_BLOCKING)
	{
		m_state |= GS_BLOCKING;
	}

	if (line.GetType() == GCodeLine::TYPE_GRBL)
	{
		return WriteGRBLLine(output, line);
	}
	else if (line.GetType() == GCodeLine::TYPE_MCODE)
	{
		return WriteMCodeLine(output, line);
	}
	else if (line.GetType() == GCodeLine::TYPE_GCODE)
	{
		return WriteGCodeLine(output, line);
	}
	else if (line.GetType() == GCodeLine::TYPE_AXIS_FEED_SPINDLE)
	{
		return WriteAxisFeedSpindleLine(output, line);
	}

	throw GhostException(GhostException::UNKNOWN_COMMAND, line.GetOriginal());
}

bool GhostConnection::WriteGRBLLine(std::string& output, const GCodeLine& line)
{
	if (line.GetGroup() == GCodeLine::GROUP_GRBL_EMPTY)
	{
		m_dqWriteBuffer.pop_front();
		return true;
	}
	else if (m_currentWrites.size() > 0)
	{
		return false;
	}
	else if (line.GetGroup() == GCodeLine::GROUP_GRBL_UNLOCK)
	{
		m_state &= ~GS_LOCKED;
	}
	else if (line.GetGroup() == GCodeLine::GROUP_GRBL_HOME)
	{
		m_state &= ~GS_LOCKED;
		m_state |= GS_HOMING;
	}
	else if (line.GetGroup() == GCodeLine::GROUP_GRBL_STATUS)
	{
		// JT probe detection change
		if (line.GetInjectedCommand())
		{
			m_state |= GS_STATUS_IGNORE;
		}

		m_state |= GS_STATUS;
		Sleep(700);
	}
	else if (line.GetGroup() == GCodeLine::GROUP_GRBL_WCS_INFO)
	{
		m_state |= GS_WCS_M101;
	}
	else if (line.GetGroup() == GCodeLine::GROUP_GRBL_CHK_MODE)
	{
		// JT probe detection change
		if (!(m_state & GS_CHK_MODE))
		{
			m_state |= GS_CHK_MODE;
		}
	}

	return WriteLine(output, line);
}

bool GhostConnection::WriteMCodeLine(std::string& output, const GCodeLine& line)
{
	if (m_currentWrites.size() > 0)
	{
		return false;
	}
	else if (line.GetGroup() == GCodeLine::GROUP_M_USER_DEFINED)
	{
		std::smatch sm;
		if (std::regex_match(line.GetCleaned(), sm, RXM1XX))
		{
			EchoLine(line.GetCleaned(), line.GetOriginal());

			if (sm[1] == "100")
			{
				M100().Execute(*this, sm[2].str());
			}
			else if (sm[1] == "101")
			{
				M101().Execute(*this, sm[2]);
			}

			m_readCache.push("ok");
			m_dqWriteBuffer.pop_front();

			return true;
		}
		else
		{
			throw GhostException(GhostException::UNKNOWN_COMMAND);
		}
	}

	return WriteLine(output, line);
}

bool GhostConnection::WriteGCodeLine(std::string& output, const GCodeLine& line)
{
	if (m_currentWrites.size() > 0 && (m_lastGGroup != GCodeLine::GROUP_G_MOTION || line.GetGroup() != GCodeLine::GROUP_G_MOTION))
	{
		return false;
	}
	else
	{
		m_lastGGroup = line.GetGroup();
	}

	return WriteLine(output, line);
}

bool GhostConnection::WriteAxisFeedSpindleLine(std::string& output, const GCodeLine& line)
{
	if (m_currentWrites.size() > 0 && m_lastGGroup != GCodeLine::GROUP_G_MOTION)
	{
		return false;
	}
	else
	{
		m_lastGGroup = GCodeLine::GROUP_G_MOTION;
	}

	return WriteLine(output, line);
}

bool GhostConnection::WriteLine(std::string& output, const GCodeLine& line)
{
	if (m_state & GS_HOMING)
	{
		if (line.GetType() != GCodeLine::TYPE_GRBL || line.GetGroup() != GCodeLine::GROUP_GRBL_HOME)
		{
			m_state &= ~GS_HOMING;
		}
	}

	std::string cleaned = line.GetCleaned();
	std::string original = line.GetOriginal();
	CleanLineIfFeedRateChange(line, cleaned, original);

	const std::string t0 = (m_flags & WRITE_CLEAN) ? cleaned : original;
	const unsigned long t0Length = t0.length();

	unsigned int totbufflen = 127;
	if ((m_state & GS_STATUS) || (m_state & GS_CHK_MODE)) //} || m_state & GS_WCS_M101) {
	{
		totbufflen = 3;
	}

	if (t0Length + 1 + m_currentWrites.total() > totbufflen)
	{
		return false;
	}

	if (t0Length > 0)
	{
		output += t0 + "\n";
		m_currentWrites.push(t0Length + 1);
	}

	//EchoLine(t0, original);

	m_dqWriteBuffer.pop_front();
	return true;
}

void GhostConnection::EchoLine(const std::string& cleaned, const std::string& original)
{
	if (m_flags & ECHO_ON)
	{
		if (m_flags & ECHO_ORIGINAL || !(m_flags & WRITE_CLEAN))
		{
			m_readCache.push(original);
		}
		else
		{
			m_readCache.push(cleaned);
		}
	}
}

void GhostConnection::WriteWithTimeout(const std::string& stringToWrite, const int timeout) const
{
	DDLogger::Log("GhostConnection::WriteWithTimeout() - Writing: " + stringToWrite);
	GhostDisplayManager::AddLine(ELineType::WRITE, stringToWrite);
	if (!OSUtility::WriteToFile(m_file, stringToWrite.c_str(), stringToWrite.length()))
	{
		throw GhostException(GhostException::FAILED_WRITE);
	}

	Sleep(timeout);
}

//////////////////////////////////////////////////////
// FeedRate
//////////////////////////////////////////////////////

void GhostConnection::SetFeedRate(const int pfeedrate)
{
    if (LockUtility::ObtainLock(m_ghSemaphore))
	{
		m_sliderValue = pfeedrate;
		m_feedRateChanged = true;
		LockUtility::ReleaseLock(m_ghSemaphore);
    }
}

void GhostConnection::UpdateFeedRate()
{
	if (m_feedRateChanged)
	{
		DDLogger::Log("GhostConnection::UpdateFeedRate - Feedrate changed. Updating feed rate.");
		if (LockUtility::ObtainLock(m_ghSemaphore))
		{
			// TODO: Confirm this code
			const int fd = (m_sliderValue * m_sfeedrate) / 100;
			if (fd > 0)
			{
				const std::string to = "F" + std::to_string(fd);
				m_dqWriteBuffer.insert(m_dqWriteBuffer.begin(), GCodeLine(to, true));
			}

			m_feedRateChanged = false;
			LockUtility::ReleaseLock(m_ghSemaphore);
		}
	}
}

bool GhostConnection::CleanLineIfFeedRateChange(const GCodeLine& line, std::string& cleaned, std::string& original)
{
	bool feedRateChanged = false;

	std::smatch sm;
	if (std::regex_match(cleaned, sm, CMDFEEDRATE) && !line.GetInjectedCommand())
	{
		if (LockUtility::ObtainLock(m_ghSemaphore))
		{
			m_sfeedrate = stoi(sm[1].str());
			const int fd = (m_sliderValue * m_sfeedrate) / 100;

			const std::string to = "F" + std::to_string(fd);
			const std::string from = "F" + std::to_string(m_sfeedrate);

			if (fd > 0)
			{
				cleaned.replace(cleaned.find(from), from.length(), to);
				original.replace(original.find(from), from.length(), to);
			}

			feedRateChanged = true;
			LockUtility::ReleaseLock(m_ghSemaphore);
		}
	}

	return feedRateChanged;
}