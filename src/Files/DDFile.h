#pragma once

#include "archive.h"
#include "manifest.h"

#include <vector>
#include <string>

/*
 * Wraps Manifest and Archive to give a simple way of working with DD files
 */
class DDFile
{
	Archive m_archive;
	Manifest m_manifest;

	void SaveFileInternal(const std::string& file, const std::string& path);

public:
	DDFile(const std::string& path);

	Job& GetJob(const std::string& jobName);
	const std::vector<Job>& GetJobs();//gets the full list of jobs contained in the DD file

	void ReadFile(const std::string& path, std::vector<unsigned char>& vuc);
	void ReadFile(const std::string& path, std::vector<std::string>& vs);

	void SaveFiles(const std::vector<std::string>& files, const std::string& path);
	std::vector<std::string> ListFiles();

	inline const std::string& GetPath() const { return m_archive.GetPath(); }
};