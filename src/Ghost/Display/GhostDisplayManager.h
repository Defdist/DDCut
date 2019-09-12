#pragma once

#include "LineType.h"

#include <string>
#include <vector>
#include <utility>
#include <mutex>

class GhostDisplayManager
{
public:
	static void AddLine(const ELineType lineType, const std::string& line);
	static std::vector<std::pair<ELineType, std::string>> GetLines();
	static void Clear();

private:
	static GhostDisplayManager& GetInstance();

	std::mutex m_mutex;
	std::vector<std::pair<ELineType, std::string>> m_lines;
};