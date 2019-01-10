#pragma once

// Forward Declarations
class GhostConnection;

class ConnectionInitializer
{
public:
	bool InitializeConnection(GhostConnection& ghostConnection) const;

private:
	void WaitForStartup(GhostConnection& ghostConnection) const;
	void HandleFirmwareUpgrade(GhostConnection& ghostConnection) const;
};