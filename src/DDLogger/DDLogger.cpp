#include "DDLogger.h"
#include "Logger.h"

namespace DDLogger
{
	Logger* INSTANCE = nullptr;

	DD_LOGGER_API bool Log(const std::string& eventText)
	{
		if (INSTANCE == nullptr)
		{
			INSTANCE = new Logger();
		}

		return  INSTANCE->Log(eventText);
	}

	DD_LOGGER_API std::string GetLogPath()
	{
		return Logger::GetLogPath();
	}

	DD_LOGGER_API std::string ReadLog()
	{
		if (INSTANCE == nullptr)
		{
			INSTANCE = new Logger();
		}

		return INSTANCE->ReadLog();
	}

	DD_LOGGER_API void Flush()
	{
		if (INSTANCE != nullptr)
		{
			INSTANCE->Flush();
		}
	}

	DD_LOGGER_API void Shutdown()
	{
		delete INSTANCE;
		INSTANCE = nullptr;
	}
}