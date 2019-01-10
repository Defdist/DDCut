#pragma once

#include <vector>
#include <string>

#include "minizip/unzip.h"

#ifdef _WIN32
	#include "minizip/iowin32.h"
	#define USEWIN32IOAPI
#endif

/*
 * Thin wrapper on minizip's unzip library to give simple object oriented access to a zip file
 */
class Archive
{
private:

	std::string m_path;
	unzFile m_unzFile;

public:
	Archive(const std::string& path);

	void Open();
	void Close();

	void ReadFile(const std::string& path, std::vector<std::string>& vs);//reads the file of path p contained in a zip file as a vector of strings where each string is a line
	void ReadFile(const std::string& path, std::vector<unsigned char>& vuc);//reads the file of path p contained in a zip file as a vector of bytes
	void CheckFile(const std::string& path) const;
	std::vector<std::string> ListFiles();

	inline const std::string& GetPath() const { return m_path; }
};