#pragma once

#include "GhostConnection.h"
#include "GhostException.h"

class GhostErrorHandler
{
public:
	static std::string GetErrorMessage(GhostConnection& connection, const GhostException& exception);

	void HandleFailure(GhostConnection& connection) const;

private:
	static std::string GetErrorMessage_Internal(GhostConnection& connection, const GhostException& exception);
	static bool WriteToGhostGunner(GhostConnection& connection);
	static std::string HandleProbeFailure(GhostConnection& connection);
};