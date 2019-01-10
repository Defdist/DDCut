#include "ProbeHelper.h"

#include "GhostConnection.h"
#include "GhostException.h"
#include "GhostRegex.h"

#include <regex>

bool ProbeHelper::IsProbeStateClear(const GhostConnection& connection) const
{
	connection.WriteWithTimeout("$?\n", 1000);

	std::string readBuffer = "";

	std::string line;
	while (connection.ReadSingleLine(line))
	{
		readBuffer += line;
	}

	std::string s;
	const std::size_t found = readBuffer.find('>');
	if (found != std::string::npos)
	{
		readBuffer = readBuffer.substr(0, found + 1);
	}

	bool probeClear = false;

	std::smatch sm;
	if (std::regex_match(s, sm, Ghost::Regex::RXSTATUS))
	{
		if (sm[18] == "0")
		{
			probeClear = true;
		}
	}

	return probeClear;
}