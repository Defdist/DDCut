#pragma once

#include "OSFile.h"

#include <string>

class OSUtility
{
public:
	static std::string GetExecPath();

	// File access
	static bool WriteToFile(const OS_FILE file, const char* pc, const int num);
	static int ReadFromFile(const OS_FILE file, char* pc, const int num);
    
    static bool ExecuteCommandInNewProcess(const std::string& directory, const std::string& command);

	static void ShowMessageBox(const std::string& title, const std::string& message);
	static bool ShowOkCancelMessageBox(const std::string& title, const std::string& message);
};
