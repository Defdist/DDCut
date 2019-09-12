#include "GhostException.h"

GhostException::GhostException(const EGhostException t)
	: GhostException(t, "")
{

}

GhostException::GhostException(const EGhostException t, const std::string& s) 
	: m_type(t)
{
	m_errorDetail = s;

	const std::string errorMessage = GetTypeMessage();

	if (!m_errorDetail.empty())
	{
		m_combinedMessage = errorMessage + " - " + m_errorDetail;
	}
	else
	{
		m_combinedMessage = errorMessage;
	}
}

std::string GhostException::GetTypeMessage() const
{
	switch (m_type)
	{
		case NO_ACCESS:
			return "no access to /dev";
		case NO_DEVICE:
			return "no Ghost Gunner found";
		case FAILED_OPEN:
			return "failed to open connection to Ghost Gunner";
		case FAILED_GET:
			return "failed to get properties of Ghost Gunner";
		case FAILED_SET:
			return "failed to set properties of Ghost Gunner";
		case FAILED_WRITE:
			return "failed to write to Ghost Gunner";
		case NOT_TTY:
			return "not a tty connection";
		case NOT_OPEN:
			return "connection to Ghost Gunner not open";
		case GRBL_ERROR:
			return "Not a valid GRBL command.";
		case ALARM:
			return "Alarm: unknown";
		case ALARM_LIMIT:
			return "Alarm: hard/soft limit hit";
		case ALARM_PROBE:
			return "Alarm: probe fail";
		case UNKNOWN_COMMAND:
			return "Not a recognized G/M/$ or other command";
		case TIMEOUT:
			return "timeout";
        case M100_OUTOFRANGE:
            return "M100 command failed with result out of range.  Please verify that Probe has same units (inches or mm) as M100 call.";
        case M101_FAIL:
            return "M101 Command failed";
		case NO_PROBE_COORD:
			return "No Probe coordinates were found to return to.";
		default:
			return "";
	}
}

std::string GhostException::GetRawDetailMessage() const
{
	return m_errorDetail;
}

const char* GhostException::what() const noexcept
{
	return m_combinedMessage.c_str();
}

GhostException::EGhostException GhostException::getType() const
{
	return m_type;
}


