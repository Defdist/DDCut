#pragma once

#include <vector>
#include <string>

/*
 * Utility functions so that reading/writing files & directories is abstracted.
 */
class FileUtility
{
public:
	static void WriteFile(const std::string& path, const std::vector<unsigned char>& vuc); // writes the file at path p based on the vector of bytes
	static bool MakeDirectory(const std::string& path, const std::string& dir);
	static std::string GetFileName(const std::string& path);
    
    static bool GetWorkingDirectory(std::string& currentDirectory);
    static bool SetWorkingDirectory(const std::string& newDirectory);
};
