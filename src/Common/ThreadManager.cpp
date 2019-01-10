#include "ThreadManager.h"

// TODO: Implement locking

ThreadManager& ThreadManager::GetInstance()
{
	static ThreadManager threadManager;
	return threadManager;
}

std::string ThreadManager::GetCurrentThreadName() const
{
	std::thread::id threadId = std::this_thread::get_id();

	if (m_threadNamesById.find(threadId) != m_threadNamesById.end())
	{
		return m_threadNamesById.find(threadId)->second;
	}

	return "";
}

void ThreadManager::SetThreadName(const std::thread::id& threadId, const std::string& threadName)
{
	m_threadNamesById[threadId] = threadName;
}

void ThreadManager::SetCurrentThreadName(const std::string& threadName)
{
	m_threadNamesById[std::this_thread::get_id()] = threadName;
}