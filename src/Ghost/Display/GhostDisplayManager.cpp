#include "GhostDisplayManager.h"

GhostDisplayManager& GhostDisplayManager::GetInstance()
{
	static GhostDisplayManager instance;
	return instance;
}

void GhostDisplayManager::AddLine(const ELineType lineType, const std::string& line)
{
	GhostDisplayManager& instance = GetInstance();
	std::unique_lock<std::mutex> lock(instance.m_mutex);

	instance.m_lines.push_back(std::make_pair<ELineType, std::string>(std::move(ELineType(lineType)), std::string(line)));
}

std::vector<std::pair<ELineType, std::string>> GhostDisplayManager::GetLines()
{
	GhostDisplayManager& instance = GetInstance();
	std::unique_lock<std::mutex> lock(instance.m_mutex);

	std::vector<std::pair<ELineType, std::string>> lines = instance.m_lines;
	instance.m_lines.clear();

	return lines;
}

void GhostDisplayManager::Clear()
{
	GhostDisplayManager& instance = GetInstance();
	std::unique_lock<std::mutex> lock(instance.m_mutex);

	instance.m_lines.clear();
}