#include "DDUpdater.h"
#include "tinyxml2.h"

#include <filesystem>
#include <RestClient/DDRestClient.h>
#include <RestClient/FileDownloader.h>
#include <Common/OSUtility.h>
#include <DDLogger/DDLogger.h>

// * Download files from S3 to PACKAGE_DIR="<DDCUT_PATH>/update/<Latest_Version>/"
// * Create SCRIPT_FILE="<DDCUT_PATH>/update/file_list.xml"
// * Execute: `updater --install-dir <DDCUT_PATH> --package-dir <PACKAGE_DIR> --script <SCRIPT_FILE> --mode main --wait <DDCUT_PROCESS_ID>`
// * Exit current process
bool DDUpdater::UpdateDDCut(const std::string& exeName, const std::string& currentVersion)
{
	std::unique_ptr<SoftwareUpdateStatus> pStatus = DDRestClient().CheckForSoftwareUpdates(currentVersion);
	if (pStatus != nullptr)
	{
		const std::string latestVersion = pStatus->LATEST_VERSION;

		const std::string installPath = std::filesystem::current_path().string();
		const std::string packagePath = installPath + "/update/" + latestVersion;
		std::filesystem::create_directories(packagePath);

		// 1. Download files from s3
		std::vector<std::string> addedFiles;
		for (auto addedFile : pStatus->ADDED_FILES)
		{
			if (!FileDownloader().DownloadFile(addedFile.URL, packagePath + "/" + addedFile.PATH))
			{
				DDLogger::Log("DDUpdater::UpdateDDCut - Failed to download " + addedFile.URL);
				return false;
			}

			addedFiles.push_back(addedFile.PATH);
		}

		for (auto changedFile : pStatus->CHANGED_FILES)
		{
			if (!FileDownloader().DownloadFile(changedFile.URL, packagePath + "/" + changedFile.PATH))
			{
				DDLogger::Log("DDUpdater::UpdateDDCut - Failed to download " + changedFile.URL);
				return false;
			}

			addedFiles.push_back(changedFile.PATH);
		}

		// 2. Create Manifest xml
		if (!CreateFileList(exeName, installPath + "/update/file_list.xml", addedFiles, pStatus->DELETED_FILES))
		{
			DDLogger::Log("DDUpdater::UpdateDDCut - Failed to create manifest xml for version " + latestVersion);
			return false;
		}

		// 3. Call Updater
		return ExecuteUpdater(installPath, packagePath);
	}

	DDLogger::Log("DDUpdater::UpdateDDCut - No updates found.");

	return false;
}

bool DDUpdater::ExecuteUpdater(const std::string& installPath, const std::string& packagePath)
{
	const unsigned long processId = GetCurrentProcessId();
	const std::string command = "updater.exe --install-dir \"" + installPath + "\" --package-dir \"" + packagePath + "\" --script \"" + installPath + "/update/file_list.xml\" --mode setup --wait " + std::to_string(processId);
	return OSUtility::ExecuteCommandInNewProcess(installPath, command);
}

bool DDUpdater::CreateFileList(const std::string& exeName, const std::string& fileName, const std::vector<std::string>& addedFiles, const std::vector<std::string>& deletedFiles)
{
	tinyxml2::XMLDocument fileListXML;

	tinyxml2::XMLElement* pUpdateElement = fileListXML.NewElement("update");
	pUpdateElement->SetAttribute("version", 3);

	pUpdateElement->InsertFirstChild(fileListXML.NewElement("dependencies"));

	tinyxml2::XMLElement* pInstallElement = fileListXML.NewElement("install");
	pUpdateElement->InsertEndChild(pInstallElement);

	for (const std::string& addedFile : addedFiles)
	{
		tinyxml2::XMLElement* pFileElement = fileListXML.NewElement("file");

		tinyxml2::XMLElement* pNameElement = fileListXML.NewElement("name");
		pNameElement->InsertFirstChild(fileListXML.NewText(addedFile.c_str()));
		pFileElement->InsertEndChild(pNameElement);

		tinyxml2::XMLElement* pPermissionsElement = fileListXML.NewElement("permissions");
		pPermissionsElement->InsertFirstChild(fileListXML.NewText("0755"));
		pFileElement->InsertEndChild(pPermissionsElement);

		if (addedFile == exeName)
		{
			tinyxml2::XMLElement* pMainBinaryElement = fileListXML.NewElement("is-main-binary");
			pMainBinaryElement->InsertFirstChild(fileListXML.NewText("true"));
			pFileElement->InsertEndChild(pMainBinaryElement);
		}

		pInstallElement->InsertEndChild(pFileElement);
	}

	tinyxml2::XMLElement* pUninstallElement = fileListXML.NewElement("uninstall");
	pUpdateElement->InsertEndChild(pUninstallElement);

	for (const std::string& deletedFile : deletedFiles)
	{
		tinyxml2::XMLElement* pFileElement = fileListXML.NewElement("file");
		pFileElement->InsertFirstChild(fileListXML.NewText(deletedFile.c_str()));
		pUninstallElement->InsertEndChild(pFileElement);
	}

	fileListXML.InsertFirstChild(pUpdateElement);
	fileListXML.SaveFile(fileName.c_str(), false);

	return true;
}