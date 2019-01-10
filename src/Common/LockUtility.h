#pragma once

// Forward Declarations
typedef void* HANDLE;

class LockUtility
{
public:
	static HANDLE CreateLock();
	static bool ObtainLock(const HANDLE lockHandle);
	static void ReleaseLock(const HANDLE lockHandle);
};