#pragma once

#include "GhostException.h"
#include "Point.h"
#include "coordinate.h"
#include "GhostConstants.h"
#include "GhostGunner.h"
#include "CurrentWrites.h"

#include <Common/defines.h>
#include <Common/OSFile.h>
#include <Files/GCodeLine.h>
#include <Files/GCodeFile.h>

#include <iostream>
#include <map>
#include <regex>
#include <chrono>
#include <string>

typedef void* HANDLE;

/*
 * The class for dealing with the actual connection to a GhostGunner machine.
 * A lot of state is maintained to deal with GRBL.
 */
class GhostConnection
{
	OS_FILE m_file;

	unsigned int m_flags = Ghost::ECHO_ON | Ghost::ECHO_ORIGINAL | Ghost::WRITE_CLEAN | Ghost::ERROR_EXCEPTION_ON;
	const GhostGunner m_ghostGunner;

	std::queue<std::string> m_readCache; // TODO: Can probably get rid of this and handle echo another way.

	std::chrono::system_clock::time_point m_lastReadTime;
	std::chrono::seconds m_timeout = std::chrono::seconds(580);

	// TODO: Figure out what these are for.
	std::deque<GCodeLine> m_dqWriteBuffer;
	CurrentWrites m_currentWrites;
	std::string m_readBuffer = "";

	int m_lastGGroup = -1;
	int m_sfeedrate = 100;  // last saved feedrate
	int m_sliderValue = 100;
	HANDLE m_ghSemaphore;
	bool m_feedRateChanged = false;

	unsigned int m_state = 0;
	std::string m_err; // TODO: Create an enum

	std::vector<Coordinate> m_machinePosition;

	void CleanState(); // used internally to reset state after a disconnect or reset
	void connectOS(); // the OS specific implementation of connect
	void disconnectOS(); // the OS specific implementation of disconnect

	void EchoLine(const std::string& cleaned, const std::string& original);


	bool WriteNextLineInCache(std::string& output); // If false is returned, stop writing cache.
	bool WriteGRBLLine(std::string& output, const GCodeLine& line);
	bool WriteMCodeLine(std::string& output, const GCodeLine& line);
	bool WriteGCodeLine(std::string& output, const GCodeLine& line);
	bool WriteAxisFeedSpindleLine(std::string& output, const GCodeLine& line);
	bool WriteLine(std::string& output, const GCodeLine& line);

	void ProcessReadLine(const std::string& line);

public:
	GhostConnection(const GhostGunner& ghostGunner);

	inline const GhostGunner& GetGhostGunner() const { return m_ghostGunner; }
	inline const std::string& GetPath() const { return m_ghostGunner.GetPath(); }
	inline const OS_FILE GetFile() const { return m_file; }

	// Connect/Disconnect
	void connect(); // connects to the device, actual connection is handled by the OS specific function
	void disconnect(); // disconnects from the device, actual connection is handled by the OS specific function
	void reconnect(); // like reset, but does a full disconnect and connect
	void reset(); // resets the device by sending a ^X signal

	void ClearProbeStatus();

	//std::string ResetGGVars();
	void SetGGParms();

	// Coordinates
	float getXCoordinate(int idx = 0);
	float getYCoordinate(int idx = 0);
	float getZCoordinate(int idx = 0);
	void clearCoordinates();

	std::map<std::string, Point3> GetPoints() const;

	// Feed Rate
	inline int GetFeedRate() const { return m_sliderValue; }
	void UpdateFeedRate();
	void SetFeedRate(const int pfeedrate); // TODO: Currently unused.
	bool CleanLineIfFeedRateChange(const GCodeLine& line, std::string& cleaned, std::string& original);

	inline bool IsConnected() const { return (m_state & Ghost::Status::GS_CONNECTED); }
	inline bool IsReadBufferEmpty() const { return m_readCache.empty(); }

	// TODO: Create state object with options for checking and updating flags.

	unsigned int getState(); // returns the state flags
	inline void SetStateFlag(const unsigned int statusFlag) { m_state |= statusFlag; }
	inline void UnsetStateFlag(const unsigned int statusFlag) { m_state &= ~statusFlag; }

	inline const std::string& GetError() const { return m_err; }
	inline void setTimeout(const std::chrono::seconds s) { m_timeout = s; } // sets the time before the timeout flag is set
	void ResetIdleTime(); // resets the time since last read and clears the timeout flag if set

	void VerifyConnected() const;

	// Send
	void send(const std::vector<std::string>& vs); // queues a vector of strings for writing
	void send(const std::string& s); // queues a string for writing
	void send(const std::vector<GCodeLine>& vl); // queues a vector of GCodeLines for writing
	void send(const GCodeLine& l); // queues a single GCodeLine for writing
	void send(const GCodeFile& f); // queues a GCodeFile for writing

	bool WriteCache(); // writes currently queued GCodeLines, has to deal with some GRBL limitations

	bool ReadLine(std::string& s); // reads a line from output into string s, returns false if nothing is read
	void flushReads() const; // clears all reads
	size_t queueSize() const { return m_dqWriteBuffer.size(); }

	void WriteWithTimeout(const std::string& stringToWrite, const int timeout) const;
	std::string ReadLineAndFlush() const;
	bool ReadSingleLine(std::string& line) const;
};