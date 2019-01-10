#pragma once

#include "FirmwareVersion.h"

#include <atomic>
#include <string>
#include <map>

// Forward Declarations
class GhostConnection;

class GhostFirmwareManager
{
public:
	static GhostFirmwareManager& GetInstance();

	FirmwareVersion GetFirmwareVersion(GhostConnection& connection) const;
	static void UploadFirmware(GhostConnection& connection, const std::string firmwareURL);
	inline int GetFirmwareUploadStatus() const { return m_uploadStatus.load(); }
	bool LoadFirmware(GhostConnection& connection, const std::string& hexFile);

private:

	mutable std::map<std::string, FirmwareVersion> m_cachedFirmwareVersionsBySerialNumber;
	std::atomic_int m_uploadStatus;

	GhostFirmwareManager() = default;
};
