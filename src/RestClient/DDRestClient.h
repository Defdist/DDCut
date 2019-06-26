#pragma once

#include <Common/ImportExport.h>
#include "CustServiceReqError.h"
#include "AvailableFirmware.h"
#include <string>
#include <memory>

#ifdef REST_CLIENT
#define REST_CLIENT_API EXPORT
#else
#define REST_CLIENT_API IMPORT
#endif

// Forward Declarations
class RestResponse;
namespace Json { class Value; }

class REST_CLIENT_API DDRestClient
{
public:
	static std::unique_ptr<CustServiceReqError> SendCustomerServiceRequest(const std::string& name, const std::string& email, const std::string& description, const std::string& ddcutVersion, const std::string& logText);
	static std::vector<AvailableFirmware> CheckForFirmwareUpdates(const std::string& ddcutVersion, const std::string& firmwareVersion);

private:
	static bool ParseResponse(const RestResponse& response, Json::Value& rootNode);
};