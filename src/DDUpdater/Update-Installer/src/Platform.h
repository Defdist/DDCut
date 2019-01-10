#pragma once

// basic platform defines
#ifdef __linux__
 #define PLATFORM_LINUX
#endif

#ifdef __FreeBSD__
 #define PLATFORM_FREEBSD
#endif

#ifdef WIN32
 #define PLATFORM_WINDOWS
 #include <windows.h>

 // disable warnings about exception specifications,
 // which are not implemented in Visual C++
 #pragma warning(disable:4290)
#endif

#ifdef __APPLE__
 #define PLATFORM_MAC
#endif

#if defined(PLATFORM_LINUX) || defined(PLATFORM_MAC) || defined(PLATFORM_FREEBSD)
 #define PLATFORM_UNIX
#endif

// platform-specific type aliases
#if defined(PLATFORM_UNIX)
 #include <unistd.h>
 #define PLATFORM_PID pid_t
#else
 #define PLATFORM_PID DWORD
#endif
