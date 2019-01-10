#pragma once

#include "GhostConnection.h"

class GhostErrorHandler
{
public:
	void HandleFailure(GhostConnection& connection) const;

private:
	bool WriteToGhostGunner(GhostConnection& connection) const;
	void HandleProbeFailure(GhostConnection& connection) const;
};