#pragma once

#include "GhostConnection.h"
#include "files/job.h"
#include "files/operation.h"
#include "GhostGunner.h"

#include <list>
#include <string>

class GhostGunnerManager
{
public:
	static GhostGunnerManager& GetInstance();

	GhostConnection* GetConnection();
	bool SetSelectedGhostGunner(const GhostGunner& ghostGunner);
	void SetSelectedGhostGunner(GhostConnection* pGhostConnection);

	void ShutdownGhostGunner(Job* pJob, Operation* pOperation); // Shuts down the GhostGunner connection and makes sure to stop the spindle if it's running
	bool ReadWriteCycle(Job* pJob, Operation* pOperation, const int hardLimitCount = 0); // ????

private:
	void HardSend(const std::string& command);

	GhostConnection* m_selectedGhostGunner = nullptr;
};