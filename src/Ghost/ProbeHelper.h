#pragma once

#include <string>

// Forward Declarations
class GhostConnection;

class ProbeHelper
{
public:
	bool IsProbeStateClear(const GhostConnection& connection) const;
};