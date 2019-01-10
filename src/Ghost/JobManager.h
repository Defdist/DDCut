#pragma once

#include "files/job.h"
#include "files/operation.h"

// Forward Declarations
class GhostConnection;

class JobManager
{
public:
	static JobManager& GetInstance();

	void AbortCurrentJob();

	inline Job* GetSelectedJob() { return m_selectedJob; }
	void SetSelectedJob(const Job& selectedJob);
	void ClearJob();

	Operation* GetCurrentOperation();
	inline int GetCurrentOperationIndex() const { return m_currentOperationIndex; }
	inline void ClearOperation() { m_currentOperationIndex = -1; }

private:
	Job* m_selectedJob = nullptr;
	int m_currentOperationIndex = -1;
};