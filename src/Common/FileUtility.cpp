#include "FileUtility.h"

#include <Logging/Logger.h>

#include <iostream>
#include <fstream>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#define FILE_SEPARATOR "\\"
#else
#define FILE_SEPARATOR "/"
#endif

void FileUtility::WriteFile(const std::string& path, const std::vector<unsigned char>& vuc)
{
	std::ofstream of(path, std::ios::out | std::ios::trunc | std::ios::binary);
    of.write((char*)(vuc.data()), vuc.size());
    of.close();
}

bool FileUtility::MakeDirectory(const std::string& path, const std::string& dir)
{
    std::error_code errorCode;
    const std::string newDir = path + FILE_SEPARATOR + dir;
    if (std::filesystem::is_directory(newDir))
    {
        return true;
    }

    return std::filesystem::create_directories(newDir, errorCode);
}

std::string FileUtility::GetFileName(const std::string& path)
{
	std::string fileName = path;
	// Remove directory if present.
	// Do this before extension removal incase directory has a period character.
	const size_t last_slash_idx = fileName.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		fileName.erase(0, last_slash_idx + 1);
	}

	return fileName;
}

bool FileUtility::GetWorkingDirectory(std::string& currentDirectory)
{
#ifdef _WIN32
	// TODO: Use std::filesystem
    const int bufferSize = MAX_PATH;
    char oldDir[bufferSize];
    if (GetCurrentDirectory(bufferSize, oldDir))
    {
        currentDirectory = oldDir;
        return true;
    }
    
    Logger::GetInstance().Log("FileUtility::GetWorkingDirectory - Error getting current directory: #" + std::to_string(GetLastError()));
#endif
    
    return false;
}

bool FileUtility::SetWorkingDirectory(const std::string& newDirectory)
{
#ifdef _WIN32
    if (SetCurrentDirectory(newDirectory.c_str()))
    {
        return true;
    }
    
    Logger::GetInstance().Log("FileUtility::SetWorkingDirectory - Error setting current directory: #" + std::to_string(GetLastError()));
#endif
    
    return false;
}
