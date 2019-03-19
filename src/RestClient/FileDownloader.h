#pragma once

#include <Common/ImportExport.h>
#include <string>
#include <fstream>

#ifdef REST_CLIENT
#define REST_CLIENT_API EXPORT
#else
#define REST_CLIENT_API IMPORT
#endif

class REST_CLIENT_API FileDownloader
{
public:
	static bool DownloadFile(const std::string& url, const std::string& location);

private:
	static void GetFile(const std::string& serverName, const std::string& getCommand, std::ofstream& outFile);
};