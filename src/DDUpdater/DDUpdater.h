#pragma once

#include <Common/ImportExport.h>
#include <vector>
#include <string>

#ifdef DD_UPDATER
#define DD_UPDATER_API EXPORT
#else
#define DD_UPDATER_API IMPORT
#endif

class DD_UPDATER_API DDUpdater
{
public:
	bool UpdateDDCut(const std::string& exeName, const std::string& currentVersion);

private:
	bool ExecuteUpdater(const std::string& installPath, const std::string& packagePath);
	bool CreateFileList(const std::string& exeName, const std::string& fileName, const std::vector<std::string>& addedFiles, const std::vector<std::string>& deletedFiles);
};