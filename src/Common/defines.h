#pragma once

// Unifies the sleep function between platforms to the windows standard Sleep which takes milliseconds

#ifdef _WIN32
#else
	#include <unistd.h>
	#define Sleep(X) usleep(X * 1000)

	#include <mach/mach_time.h>
	#define GetTickCount() mach_absolute_time()
#endif
