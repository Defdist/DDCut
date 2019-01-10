#include "JobManager.h"

#include "GhostGunnerManager.h"
#include "GhostConnection.h"
#include "common/defines.h"

JobManager& JobManager::GetInstance()
{
	static JobManager instance;
	return instance;
}

void JobManager::SetSelectedJob(const Job& selectedJob)
{
	m_selectedJob = new Job(selectedJob);
	m_currentOperationIndex = 0;
}

void JobManager::ClearJob()
{
	delete m_selectedJob;
	m_selectedJob = nullptr;

	m_currentOperationIndex = -1;
}

Operation* JobManager::GetCurrentOperation()
{
	if (m_currentOperationIndex == -1 || m_selectedJob == nullptr)
	{
		return nullptr;
	}

	return &m_selectedJob->GetOperation(m_currentOperationIndex);
}

void JobManager::AbortCurrentJob()
{
	GhostConnection* pConnection = GhostGunnerManager::GetInstance().GetConnection();
	if (pConnection != nullptr)
	{
		const double startTime = GetTickCount();
		while (!pConnection->IsReadBufferEmpty())
		{
			const double currentTime = GetTickCount() - startTime;
			if (currentTime >= 60000)
			{
				break;
			}

			Sleep(100);
		}

		Sleep(3000);
	}

	ClearJob();
}