#pragma once

#include <Common/ImportExport.h>
#include <string>

#ifdef DD_LOGGER
#define DD_LOGGER_API EXPORT
#else
#define DD_LOGGER_API IMPORT
#endif

namespace DDLogger
{
	DD_LOGGER_API bool Log(const std::string& eventText);
	DD_LOGGER_API std::string GetLogPath();
	DD_LOGGER_API std::string ReadLog();
	DD_LOGGER_API void Flush();
}