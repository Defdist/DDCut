#pragma once

#include <string>
#include <thread>
#include <map>

class ThreadManager
{
public:
	static ThreadManager& GetInstance();

	// Future: Implement a CreateThread method that takes the name, function, and parameters.
	std::string GetCurrentThreadName() const;
	void SetThreadName(const std::thread::id& threadId, const std::string& threadName);
	void SetCurrentThreadName(const std::string& threadName);

private:
	std::map<std::thread::id, std::string> m_threadNamesById;
};