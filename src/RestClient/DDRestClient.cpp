#include "DDRestClient.h"
#include "RestClient.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <asio.hpp>
#include <asio/ssl.hpp>
#include <json/json.h>

std::unique_ptr<CustServiceReqError> DDRestClient::SendCustomerServiceRequest(const std::string& name, const std::string& email, const std::string& description, const std::string& ddcutVersion, const std::string& logText)
{
	Json::Value rootNode;
	rootNode["name"] = name;
	rootNode["email"] = email;
	rootNode["description"] = description;
	rootNode["ddcut_version"] = ddcutVersion;
	rootNode["log_text"] = logText;

	Json::FastWriter writer;
	RestResponse response = RestClient::Post("/customerServiceRequest/", writer.write(rootNode));
	if (response.GetStatusCode() == 201)
	{
		return std::unique_ptr<CustServiceReqError>(nullptr);
	}
	else
	{
		CustServiceReqError error;

		Json::Value rootErrorNode;
		if (Json::Reader().parse(response.GetResponseBody(), rootErrorNode, false))
		{
			const std::vector<std::string> memberNames = rootErrorNode.getMemberNames();
			for (const std::string& name : memberNames)
			{
				Json::Value errorNode = rootErrorNode.get(name, "UNKNOWN ERROR");
				error.ERRORS[name] = errorNode.get(Json::Value::ArrayIndex(0), "UNKNOWN_ERROR").asString();
			}
		}

		return std::make_unique<CustServiceReqError>(error);
	}
}

std::unique_ptr<SoftwareUpdateStatus> DDRestClient::CheckForSoftwareUpdates(const std::string& ddcutVersion)
{
	SoftwareUpdateStatus status;

#ifdef _WIN32
	const std::string operatingSystem = "Windows";
#else
	const std::string operatingSystem = "OSX";
#endif

	RestResponse response = RestClient::Get("/updateGGSoftware/?currentVersion=" + ddcutVersion + "&operatingSystem=" + operatingSystem);

	Json::Value rootNode;
	if (ParseResponse(response, rootNode))
	{
		status.LATEST_VERSION = rootNode["latestVersion"].asString();
		status.RELEASE_NOTES = rootNode["releaseNotes"].asString();
		status.ADDED_FILES = ParseFiles(rootNode["addedFiles"]);
		status.CHANGED_FILES = ParseFiles(rootNode["changedFiles"]);

		Json::Value deletedNode = rootNode["deleted_files"];
		const size_t size = deletedNode.size();
		for (size_t i = 0; i < size; i++)
		{
			Json::Value file = deletedNode.get(Json::ArrayIndex(i), "");
			status.DELETED_FILES.emplace_back(file["relativePath"].asString());
		}

		return std::make_unique<SoftwareUpdateStatus>(status);
	}

	return std::unique_ptr<SoftwareUpdateStatus>(nullptr);
}

std::vector<AvailableFirmware> DDRestClient::CheckForFirmwareUpdates(const std::string& ddcutVersion, const std::string& firmwareVersion)
{
	std::vector<AvailableFirmware> updatesAvailable;

	RestResponse response = RestClient::Get("/updateGGFirmware/?ddcutVersion=" + ddcutVersion + "&currentFirmwareVersion=" + firmwareVersion);

	Json::Value rootNode;
	if (ParseResponse(response, rootNode))
	{
		/*
		{"status":"ok","message":"","compatible_firmware":[{"version":"2.2","s3Urls":["https://s3.amazonaws.com/ddcut-firmware-dev/2.2/DD2v2.hex"],"description":"2.2 version (1.0.1 - 1.1.0)"}]}
		*/

		Json::Value firmwareNode = rootNode["compatible_firmware"];
		for (size_t i = 0; i < firmwareNode.size(); i++)
		{
			AvailableFirmware firmwareUpdate;

			Json::Value firmware = firmwareNode.get(Json::ArrayIndex(i), "");
			firmwareUpdate.VERSION = firmware["version"].asString();
			firmwareUpdate.DESCRIPTION = firmware["description"].asString();

			Json::Value s3Node = firmware["s3Urls"];
			for (size_t j = 0; j < s3Node.size(); j++)
			{
				firmwareUpdate.FILES.emplace_back(s3Node.get(Json::ArrayIndex(j), "").asString());
			}

			updatesAvailable.emplace_back(std::move(firmwareUpdate));
		}
	}

	return updatesAvailable;
}

bool DDRestClient::ParseResponse(const RestResponse& response, Json::Value& rootNode)
{
	if (response.GetStatusCode() == 200)
	{
		if (Json::Reader().parse(response.GetResponseBody(), rootNode, false))
		{
			if (rootNode.isMember("status") && rootNode["status"] == "ok")
			{
				return true;
			}
		}
	}

	return false;
}

std::vector<UpdateFile> DDRestClient::ParseFiles(const Json::Value& filesNode)
{
	std::vector<UpdateFile> files;

	const size_t size = filesNode.size();
	for (size_t i = 0; i < size; i++)
	{
		const Json::Value file = filesNode.get(Json::ArrayIndex(i), "");

		UpdateFile updateFile;
		updateFile.PATH = file["relativePath"].asString();
		updateFile.URL = file["s3url"].asString();

		files.emplace_back(std::move(updateFile));
	}

	return files;
}