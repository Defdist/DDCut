#pragma once

#include <string>
#include <exception>
#include <cstring>

/*
exception class for handling GhostGunner specific errors
NO_ACCESS
NO_DEVICE,
FAILED_OPEN
FAILED_GET
FAILED_SET
FAILED_WRITE,
NOT_TTY
NOT_OPEN,
GRBL_ERROR
ALARM
ALARM_LIMIT
ALARM_PROBE,
UNKNOWN_COMMAND
TIMEOUT
*/
class GhostException : public std::exception
{
public:
	enum EGhostException
	{
		NO_ACCESS,
		NO_DEVICE,
		FAILED_OPEN,
		FAILED_GET,
		FAILED_SET,
		FAILED_WRITE,
		NOT_TTY,
		NOT_OPEN,
		GRBL_ERROR,
		ALARM,
		ALARM_LIMIT,
		ALARM_PROBE,
		UNKNOWN_COMMAND,
		M100_OUTOFRANGE,
		M101_FAIL,
		TIMEOUT,
		NO_PROBE_COORD
	};
private:
	EGhostException m_type;

	std::string m_errorDetail;
	std::string m_combinedMessage;
	std::string GetTypeMessage() const;

public:
	GhostException(const EGhostException t);
	GhostException(const EGhostException t, const std::string& s);
	const char* what() const noexcept;
	EGhostException getType();
};
