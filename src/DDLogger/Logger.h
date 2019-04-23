#pragma once

#include "spdlog/spdlog.h"

#include <list>

class Logger
{
public:
	static Logger& GetInstance();
	static std::string GetLogPath();

	bool Log(const std::string& eventText);
    std::string ReadLog() const;
	void Flush();

private:
	Logger();

	std::shared_ptr<spdlog::logger> m_logger;
};