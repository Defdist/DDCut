#include "DDUpdater.h"

#include <filesystem>
#include <DDRestClient.h>
#include <FileDownloader.h>
#include <chrono>

#include <zmq.h>

bool DDUpdater::UpdateDDCut(const std::string& currentVersion)
{
	std::unique_ptr<SoftwareUpdateStatus> pStatus = DDRestClient().CheckForSoftwareUpdates(currentVersion);
	if (pStatus != nullptr)
	{
		const std::string latestVersion = pStatus->LATEST_VERSION;

		const std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);

		auto currentPath = std::filesystem::current_path();
		const std::string path = currentPath.string() + "/" + latestVersion + "/" + std::to_string(seconds.count()) + "/";
		std::filesystem::create_directories(path);

		// 1. Download files from s3
		for (auto addedFile : pStatus->ADDED_FILES)
		{
			FileDownloader().DownloadFile(addedFile.URL, path + addedFile.PATH);
		}

		for (auto changedFile : pStatus->CHANGED_FILES)
		{
			FileDownloader().DownloadFile(changedFile.URL, path + changedFile.PATH);
		}

		// TODO: Finish this

		// 2. Create Manifest xml

		// 3. 

		return true;
	}

	return false;
}