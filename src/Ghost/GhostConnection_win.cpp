#ifdef _WIN32
#include "GhostConnection.h"
#include "Logging/Logger.h"

#include <windows.h>

void GhostConnection::connectOS()
{
	Logger::GetInstance().Log("GhostConnection::connectOS() - WIN32 - File Path: " + m_ghostGunner.GetPath());
	m_file = CreateFile(m_ghostGunner.GetPath().c_str(), GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if (m_file == INVALID_HANDLE_VALUE)
	{
		throw GhostException(GhostException::FAILED_OPEN, "Invalid handle");
	}

	DCB dcb = {0};
	dcb.DCBlength = sizeof(DCB);
	GetCommState(m_file, &dcb);
	dcb.BaudRate = CBR_115200;
	dcb.fBinary = FALSE;
	dcb.fParity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	//dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	//dcb.fDsrSensitivity = 0;
	//dcb.fTXContinueOnXoff = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	//dcb.fErrorChar = 0;
	dcb.fNull = FALSE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fAbortOnError = FALSE;
	//dcb.XonLim = FALSE;
	//dcb.XoffLim = FALSE;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;
	SetCommState(m_file, &dcb);

	// Set timeouts
	COMMTIMEOUTS timeout = {0};
	GetCommTimeouts(m_file, &timeout);
	timeout.ReadIntervalTimeout = MAXDWORD;
	timeout.ReadTotalTimeoutConstant = 0;
	timeout.ReadTotalTimeoutMultiplier = 0;
	timeout.WriteTotalTimeoutConstant = 0;
	timeout.WriteTotalTimeoutMultiplier = 0;
	SetCommTimeouts(m_file, &timeout);
}

void GhostConnection::disconnectOS()
{
    CloseHandle(m_file);
	m_file = INVALID_HANDLE_VALUE;
}
#endif // _WIN32
