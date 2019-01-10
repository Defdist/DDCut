#include "LockUtility.h"

#ifdef _WIN32
	#include <windows.h>
#else
    #include <string>
	#include <semaphore.h>
#endif

static int LOCK_INDEX = 0;

HANDLE LockUtility::CreateLock()
{
#ifdef _WIN32
	return CreateSemaphore(NULL, 1L, 1L, NULL);
#else
	std::string semaphoreName = "/DD_SEMAPHORE_" + std::to_string(++LOCK_INDEX);
    sem_unlink(semaphoreName.c_str());
	return (HANDLE)sem_open(semaphoreName.c_str(), O_CREAT, 0644, 1);
#endif
}

bool LockUtility::ObtainLock(const HANDLE lockHandle)
{
#ifdef _WIN32
	return WaitForSingleObject(lockHandle, 2000L) == WAIT_OBJECT_0;
#else
	return sem_wait((sem_t*)lockHandle) == 0;
#endif
}

void LockUtility::ReleaseLock(const HANDLE lockHandle)
{
#ifdef _WIN32
	ReleaseSemaphore(lockHandle, 1, NULL);
#else
    sem_post((sem_t*)lockHandle);
	//sem_close((sem_t*)lockHandle);
    //sem_unlink("/semaphore"); // TODO: Determine name
#endif
}
