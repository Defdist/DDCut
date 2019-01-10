#include "OSUtility.h"
#include "FileUtility.h"

#include <Ghost/GhostException.h>
#include <Logging/Logger.h>

#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <stdlib.h>
#include <mach-o/dyld.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <CoreFoundation/CoreFoundation.h>
#include <unistd.h>
#endif

std::string OSUtility::GetExecPath()
{
#ifdef __APPLE__
    unsigned int size = MAXPATHLEN;
    char *pathBuffer = new char[size];
    int result = _NSGetExecutablePath(pathBuffer, &size);
    if (result == -1)
    {
        delete[] pathBuffer;
        pathBuffer = new char[size];
        result = _NSGetExecutablePath(pathBuffer, &size);
        if (result == -1)
        {
            return ""; // not sure why this would fail again (probably won't ever?)
        }
    }

    // resolve symlinks (who cares .. ?)
    char *realPathBuffer = realpath(pathBuffer, NULL);
    if (realPathBuffer == NULL)
    {
        return "";
    }

    std::string appPath = realPathBuffer;
    delete[] pathBuffer;
    free(realPathBuffer);

    // _NSGetExecutablePath actually returns the path to and including the
    // currently running executable, but we just want the path containing the
    // executable.
    std::string::size_type pos = appPath.find_last_of('/');

    return appPath.substr(0, pos);

#else
	return std::filesystem::current_path().string();
#endif
}

void OSUtility::WriteToFile(const OS_FILE file, const char* pc, const int num)
{
#ifdef _WIN32
	DWORD writeSize;
	WriteFile(file, pc, num, &writeSize, NULL);
	if (num != writeSize)
	{
		throw GhostException(GhostException::FAILED_WRITE);
	}
#else
	int writeSize = write(file, pc, num);
	if (num != writeSize)
	{ 
		throw GhostException(GhostException::FAILED_WRITE);
	}
#endif
}

int OSUtility::ReadFromFile(const OS_FILE file, char* pc, const int num)
{
#ifdef _WIN32
	DWORD readSize;
	ReadFile(file, pc, num, &readSize, NULL);
	return readSize;
#else
	return read(file, pc, num);
#endif
}

bool OSUtility::ExecuteCommandInNewProcess(const std::string& directory, const std::string& command)
{
#ifdef _WIN32
    // 1. Store the old working directory
    std::string oldDirectory;
    if (!FileUtility::GetWorkingDirectory(oldDirectory))
    {
        return false;
    }
    
    // 2. Set the new working directory
    if (!FileUtility::SetWorkingDirectory(directory))
    {
        return false;
    }
    
    // 3. Allocate STARTUPINFO and PROCESS_INFORMATION objects
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    
    // 4. Create the process
    Logger::GetInstance().Log("OSUtility::ExecuteCommandInNewProcess - Command: " + command);
    if (!CreateProcess(NULL, (LPSTR)command.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        Logger::GetInstance().Log("OSUtility::ExecuteCommandInNewProcess - CreateProcess failed : " + std::to_string(GetLastError()));
        FileUtility::SetWorkingDirectory(oldDirectory);
        return false;
    }
    
    // 5. Wait for the process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    // 6. Restore original working directory
    FileUtility::SetWorkingDirectory(oldDirectory);
#elif __APPLE__
	pid_t processId;
	if ((processId = fork()) == 0)
	{
		//char app[] = "/bin/echo";
		std::string app = directory + "/" + command;
        char* appArray = new char[app.size() + 1];
        std::copy(app.begin(), app.end(), appArray);
        appArray[app.size()] = '\0';
        
        std::string success = "success";
        char* successArray = new char[success.size() + 1];
        std::copy(success.begin(), success.end(), successArray);
        successArray[success.size()] = '\0';
        
		char* const argv[] = { appArray, successArray, NULL };
		if (execv(app.c_str(), argv) < 0)
		{
			perror("execv error");
		}
        
        delete[] successArray;
        delete[] appArray;
	}
#endif

    return true;
}

void OSUtility::ShowMessageBox(const std::string& title, const std::string& message)
{
#ifdef _WIN32
	MessageBox(NULL, message.c_str(), title.c_str(), MB_ICONERROR | MB_OK);
#elif __APPLE__
	SInt32 nRes = 0;
	const void* keys[] = { kCFUserNotificationAlertHeaderKey,
		kCFUserNotificationAlertMessageKey };
	const void* vals[] = {
		CFSTR("Test Foundation Message Box"),
		CFSTR("Hello, World!")
	};

	CFDictionaryRef dict = CFDictionaryCreate(0, keys, vals,
		sizeof(keys) / sizeof(*keys),
		&kCFTypeDictionaryKeyCallBacks,
		&kCFTypeDictionaryValueCallBacks);

	CFUserNotificationRef pDlg = CFUserNotificationCreate(kCFAllocatorDefault, 0,
		kCFUserNotificationPlainAlertLevel,
		&nRes, dict);
#endif
}

bool OSUtility::ShowOkCancelMessageBox(const std::string& title, const std::string& message)
{
#ifdef _WIN32
	return MessageBox(NULL, message.c_str(), title.c_str(), MB_ICONERROR | MB_OKCANCEL | MB_DEFBUTTON2) == IDOK;
#elif __APPLE__

#endif

	return false;
}
