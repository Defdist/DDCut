#pragma once

#include <queue>

class CurrentWrites
{
public:
	inline unsigned long front()
	{
		return m_currentWrites.front();
	}

	inline unsigned long pop()
	{
		if (!m_currentWrites.empty())
		{
			const unsigned long currentWrite = m_currentWrites.front();
			m_currentWritesTotal -= currentWrite;
			m_currentWrites.pop();
			
			return currentWrite;
		}
		
		return 0;
	}
	
	void push(const unsigned long currentWrite)
	{
		m_currentWritesTotal += currentWrite;
		m_currentWrites.push(currentWrite);
	}
	
	void clear()
	{
		while (!empty())
		{
			pop();
		}
		m_currentWritesTotal = 0;
	}
	
	inline size_t size() const { return m_currentWrites.size(); }
	inline bool empty() const { return m_currentWrites.empty(); }
	inline unsigned long total() const { return m_currentWritesTotal; }
	
private:
	std::queue<unsigned long> m_currentWrites;
	unsigned long m_currentWritesTotal = 0;	
};