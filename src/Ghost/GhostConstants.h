#pragma once

#include <chrono>

namespace Ghost
{
	static const unsigned int ECHO_OFF = 0;
	static const unsigned int ECHO_ON = 1;
	static const unsigned int ECHO_SENT = 0;
	static const unsigned int ECHO_ORIGINAL = 2;
	static const unsigned int WRITE_ORIGINAL = 0;
	static const unsigned int WRITE_CLEAN = 4;
	static const unsigned int ERROR_EXCEPTION_ON = 0;
	static const unsigned int ERROR_EXCEPTION_OFF = 8;

	static const std::chrono::seconds STARTDELAY = std::chrono::seconds(2);
	
	namespace Status
	{
		// TODO: Document these
		static const unsigned int GS_CONNECTED = 1;
		static const unsigned int GS_STARTUP = 2;
		static const unsigned int GS_BOOTING = 4;
		static const unsigned int GS_ERROR = 8;
		static const unsigned int GS_LOCKED = 16;
		static const unsigned int GS_SPINDLE = 32;
		static const unsigned int GS_TIMEOUT = 64;
		static const unsigned int GS_HOMING = 128;
		static const unsigned int GS_STATUS = 256;
		static const unsigned int GS_CHK_MODE = 512;
		static const unsigned int GS_FD_UPDATE = 1024;
		static const unsigned int GS_STATUS_IGNORE = 2048;
		static const unsigned int GS_WCS_M101 = 4096;
		static const unsigned int GS_BLOCKING = GS_WCS_M101;
	}
}