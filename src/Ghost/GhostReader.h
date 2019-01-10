#pragma once

#include "GhostConnection.h"

#include <string>
#include <queue>

class GhostReader
{
public:
	GhostReader(GhostConnection& connection);

	//inline bool IsReadBufferEmpty() const { return m_readCache.empty(); }
	bool ReadLine(std::string& s); // reads a line from output into string s, returns false if nothing is read
	bool ReadSingleLine(std::string& line) const;
	std::string ReadLineAndFlush() const;

	void FlushReads() const; // clears all reads

private:
	void ProcessReadLine(const std::string& line);


	std::queue<std::string> m_readCache; // TODO: Can probably get rid of this and handle echo another way.
	GhostConnection& m_connection;
};