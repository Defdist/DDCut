#pragma once

#include <string>

/*
 * Takes a line of text and parses it for minimal G-Code representation
 * Also determines group and type of code for dealing with some limitations of GRBL
 */
class GCodeLine
{
public:
    enum commandGroup{
        GROUP_UNKNOWN=-1,

        GROUP_G_NON_MODAL=0,
        GROUP_G_MOTION=1,
        GROUP_G_PLANE_SELECTION=2,
        GROUP_G_DISTANCE=3,
        GROUP_G_ARC_DISTANCE=4,
        GROUP_G_FEED_RATE=5,
        GROUP_G_UNITS=6,
        GROUP_G_CUTTER_DIAMETER=7,
        GROUP_G_TOOL_LENGTH_OFFSET=8,
        GROUP_G_CANNED_CYCLES=10,
        GROUP_G_COORDINATE_SYSTEM=12,
        GROUP_G_CONTROL=13,
        GROUP_G_SPINDLE_SPEED=14,
        GROUP_G_LATHE_DIAMETER=15,

        GROUP_M_STOPPING=4,
        GROUP_M_IO=5,
        GROUP_M_TOOL_CHANGE=6,
        GROUP_M_SPINDLE=7,
        GROUP_M_COOLANT=8,
        GROUP_M_OVERRIDE=9,
        GROUP_M_USER_DEFINED=10,

        GROUP_GRBL_EMPTY=0,
        GROUP_GRBL_COMMAND=1,
        GROUP_GRBL_HOME=2,
        GROUP_GRBL_UNLOCK=3,
        GROUP_GRBL_SPECIAL=4,
        GROUP_GRBL_STATUS=5,
        GROUP_GRBL_CHK_MODE=6,
        GROUP_GRBL_WCS_INFO=7
    };

    enum blockingType{
        TYPE_NOT_BLOCKING=0,
        TYPE_BLOCKING=1
    };

    enum commandType{
        TYPE_UNKNOWN=-1,
        TYPE_AXIS_FEED_SPINDLE=0,
        TYPE_GCODE=1,
        TYPE_MCODE=2,
        TYPE_GRBL=3
    };

    enum probeType{
        TYPE_NOT_PROBE=-1,
        TYPE_PROBE=0
    };

private:
    void Process(std::string& s, bool injected);

	std::string m_orig;
	std::string m_clean;
	commandGroup m_group = GROUP_UNKNOWN;
	commandType m_type = TYPE_UNKNOWN;
	probeType m_probe = TYPE_NOT_PROBE;
	blockingType m_block = TYPE_NOT_BLOCKING;
	bool m_injectedCommand;

public:
	GCodeLine(const std::string& s);
	GCodeLine(const std::string& s, bool injected);

	// GETTERS
	inline const std::string& GetOriginal() const { return m_orig; } // Returns the original line
	inline const std::string& GetCleaned() const { return m_clean; } // Returns the minimal representation
	inline const commandGroup GetGroup() const { return m_group; } // Gets the GCode or MCode modal group
	inline const commandType GetType() const { return m_type; } // Gets the type: Axis Feed Spindle (Axis movement, Feed rate or Spindle speed), GCode, MCode, or GRBL command
	inline const blockingType GetBlocking() const { return m_block; }
	inline const bool GetInjectedCommand() const { return m_injectedCommand; }
};
