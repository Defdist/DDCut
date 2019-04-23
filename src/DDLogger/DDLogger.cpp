#include "DDLogger.h"
#include "Logger.h"

namespace DDLogger
{
	DD_LOGGER_API bool Log(const std::string& eventText)
	{
		return Logger::GetInstance().Log(eventText);
	}

	DD_LOGGER_API std::string GetLogPath()
	{
		return Logger::GetLogPath();
	}

	DD_LOGGER_API std::string ReadLog()
	{
		return Logger::GetInstance().ReadLog();
	}

	DD_LOGGER_API void Flush()
	{
		Logger::GetInstance().Flush();
	}
}