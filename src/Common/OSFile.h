#pragma once

#ifdef _WIN32
	#include <windows.h>
	
	typedef HANDLE OS_FILE;
#else
	typedef int OS_FILE;
#endif