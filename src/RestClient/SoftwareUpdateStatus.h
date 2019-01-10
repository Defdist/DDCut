#pragma once

#include <string>
#include <vector>

struct UpdateFile
{
	std::string URL;
	std::string PATH;
};

struct SoftwareUpdateStatus
{
	std::string LATEST_VERSION;
	std::string RELEASE_NOTES;
	std::vector<UpdateFile> ADDED_FILES;
	std::vector<UpdateFile> CHANGED_FILES;
	std::vector<std::string> DELETED_FILES;
};