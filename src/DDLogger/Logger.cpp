#include "Logger.h"

#include <Common/OSUtility.h>
#include <Common/FileUtility.h>
#include <Common/ThreadManager.h>

#include <fstream>

Logger::Logger()
{
	const bool success = FileUtility::MakeDirectory(OSUtility::GetExecPath(), "logs");
	if (success)
	{
		auto sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(GetLogPath(), 1024 * 1024, 5);
		m_logger = spdlog::create_async("LOGGER", sink, 8192, spdlog::async_overflow_policy::block_retry, nullptr, std::chrono::seconds(2));
		m_logger->log(spdlog::level::level_enum::info, OSUtility::GetExecPath());
	}
}

Logger::~Logger()
{
	spdlog::drop("LOGGER");
}

std::string Logger::GetLogPath()
{
	return OSUtility::GetExecPath() + "/logs/ddcut.log";
}

bool Logger::Log(const std::string& eventText)
{
	if (m_logger != nullptr)
	{
		std::string eventTextClean = eventText;
		while (eventTextClean.find("\n") != std::string::npos)
		{
			eventTextClean.erase(eventTextClean.find("\n"), 2);
		}

		const std::string threadName = ThreadManager::GetInstance().GetCurrentThreadName();
		if (!threadName.empty())
		{
			eventTextClean = threadName + " => " + eventTextClean;
		}

		m_logger->log(spdlog::level::level_enum::info, eventTextClean);
		return true;
	}

	return false;
}

std::string Logger::ReadLog() const
{
    std::string logs;

	const std::string path = OSUtility::GetExecPath() + "/logs/ddcut.log";
	FILE* pFile = fopen(path.c_str(), "r");
	if (pFile != nullptr)
	{
		char cstr[100];
		while (fgets(cstr, 100, pFile) != NULL)
		{
			logs += std::string(cstr);
		}

		fclose(pFile);
	}
	else
	{
		logs = "<ERROR READING LOGS>";
	}

    return logs;
}

void Logger::Flush()
{
	if (m_logger != nullptr)
	{
		m_logger->flush();
	}
}
