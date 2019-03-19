#include "GhostConnection.h"

#include "DDLogger/DDLogger.h"

#ifndef _WIN32
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>

void GhostConnection::connectOS()
{
	DDLogger::Log("GhostConnection::connectOS() - MAC - File Path: " + m_ghostGunner.GetPath());
    if ((m_file = open(m_ghostGunner.GetPath().c_str(), O_RDWR|O_NOCTTY|O_NDELAY)) < 0)
	{
        const std::string error = strerror(errno);
		throw GhostException(GhostException::FAILED_OPEN, "m_file failed to open - " + error);
	}

	if (!isatty(m_file))
	{
		throw GhostException(GhostException::NOT_TTY);
	}

	struct termios config;
	if (tcgetattr(m_file, &config) < 0)
	{
		throw GhostException(GhostException::FAILED_GET);
	}

	config.c_cflag = CS8|CREAD|CLOCAL;
	cfsetispeed(&config, B115200);
	cfsetospeed(&config, B115200);
	if (tcsetattr(m_file, TCSANOW, &config) < 0)
	{
		throw GhostException(GhostException::FAILED_SET);
	}
}

void GhostConnection::disconnectOS()
{
    close(m_file);
	m_file = -1;
}
#endif // _WIN32
