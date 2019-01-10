#include "GCodeFile.h"

#include "DDException.h"

GCodeFile::GCodeFile(const std::vector<std::string>& ls)
{
	Load(ls);
}

void GCodeFile::Load(const std::vector<std::string>& ls)
{
	m_gcodeLines.reserve(ls.size());

	// TODO: Why duplicate this here and inside loop below?
	if (LookAhead("G38.", 0, 30, ls) > 0) // http://linuxcnc.org/docs/html/gcode/g-code.html#gcode:g38
	{
		m_gcodeLines.push_back(GCodeLine("$?", true));
	}

	for (size_t i = 0; i < ls.size(); ++i)
	{
		// JT probe detection change
        if (LookAhead("G38.", i, 1, ls) > 0) // http://linuxcnc.org/docs/html/gcode/g-code.html#gcode:g38
		{
			m_gcodeLines.push_back(GCodeLine("$?")); // TODO: Why isn't GCodeLine injected?
        }

        if (LookAhead("M101", i, 1, ls) > 0)
		{
			// Wait for 0.1 seconds (http://linuxcnc.org/docs/html/gcode/g-code.html#gcode:g4)
			m_gcodeLines.push_back(GCodeLine("G4 P0.1")); // TODO: Why isn't GCodeLine injected?
        }

		m_gcodeLines.push_back(GCodeLine(ls[i]));
	}
}

// JT probe detection change
int GCodeFile::LookAhead(const std::string &s, int start, int numlines, const std::vector<std::string>& ls) const
{
    int rv = -1;
    int x;

	if ((int)ls.size() < start + numlines)
	{
		x = (int)ls.size();
	}
	else
	{
		x = start + numlines;
	}

    for (int i = start; i < x; ++i)
	{
        if (ls[i].find(s) != std::string::npos)
		{
            rv = i;
        }
    }

    return rv;
}