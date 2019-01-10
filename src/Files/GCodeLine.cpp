#include "GCodeLine.h"

#include <Ghost/GhostRegex.h>

GCodeLine::GCodeLine(const std::string& s, bool injected)
{
	std::string dupS = s;
	Process(dupS, injected);
}

GCodeLine::GCodeLine(const std::string& s)
{
	std::string dupS = s;
    Process(dupS, false);
}

void GCodeLine::Process(std::string& s, bool injected)
{
	m_injectedCommand = injected;
	if (s.find("(") == 0)
	{
        if (s.find(")") !=  0)
		{
            s.append(sizeof(char), ')');
        }
	}
	m_orig = s;

	bool comment = false;
	for (unsigned int i = 0;i < s.length(); ++i)
	{
		if (s[i] == ';' || s[i] == '\r' || s[i] == '\n')
		{
			break;
		}
		else if (s[i] == '(')
		{
			comment=true;
		}
		else if (s[i] == ')')
		{
			comment=false;
		}
		else if (!comment && s[i] != ' ' && s[i] != '\t')
		{
			m_clean.push_back(s[i]);
		}
	}

	m_block = TYPE_NOT_BLOCKING;
	std::smatch sm;
	if (std::regex_match(m_clean, sm, Ghost::Regex::RXAFS))
	{
		m_type = TYPE_AXIS_FEED_SPINDLE;
		m_group = GROUP_G_MOTION;
	}
	else if (std::regex_match(m_clean, sm, Ghost::Regex::RXGCODE))
	{
		m_type = TYPE_GCODE;

		if (sm[1]=="4" || sm[1]=="10" || sm[1]=="28" || sm[1]=="30" || sm[1]=="53" || sm[1]=="92")
		{
			m_group = GROUP_G_NON_MODAL;
			m_block = TYPE_BLOCKING;
		}
		else if (sm[1]=="0" || sm[1]=="1" || sm[1]=="2" || sm[1]=="3" || sm[1]=="38" || sm[1]=="80")
		{
		    if (sm[1]=="38")
			{
				m_probe = TYPE_PROBE;
		    }

			m_group = GROUP_G_MOTION;
		}
		else if (sm[1]=="17" || sm[1]=="18" || sm[1]=="19")
		{
			m_group = GROUP_G_PLANE_SELECTION;
		}
		else if (sm[1]=="90" || sm[1]=="91")
		{
			m_group = GROUP_G_DISTANCE;
		}
		else if (sm[1]=="93" || sm[1]=="94")
		{
			m_group = GROUP_G_FEED_RATE;
		}
		else if (sm[1]=="20" || sm[1]=="21")
		{
			m_group = GROUP_G_UNITS;
		}
		else if (sm[1]=="43" || sm[1]=="49")
		{
			m_group = GROUP_G_TOOL_LENGTH_OFFSET;
		}
		else if (sm[1]=="54" || sm[1]=="55" || sm[1]=="56" || sm[1]=="57" || sm[1]=="58" || sm[1]=="59")
		{
			m_group = GROUP_G_COORDINATE_SYSTEM;
			m_block = TYPE_BLOCKING;
		}
	}
	else if (std::regex_match(m_clean, sm, Ghost::Regex::RXMCODE))
	{
		m_type = TYPE_MCODE;

		if (sm[1]=="0" || sm[1]=="1" || sm[1]=="2" || sm[1]=="30")
		{
			m_group = GROUP_M_STOPPING;
		}
		else if (sm[1]=="3" || sm[1]=="4" || sm[1]=="5")
		{
			m_group = GROUP_M_SPINDLE;
		}
		else if (sm[1]=="7" || sm[1]=="8" || sm[1]=="9")
		{
			m_group = GROUP_M_COOLANT;
		}
		else if (sm[1]=="100" || sm[1]=="101" || sm[1]=="102")
		{
			m_group = GROUP_M_USER_DEFINED;
		}
	}
	else if (std::regex_match(m_clean, sm, Ghost::Regex::RXGRBL))
	{
		m_type = TYPE_GRBL;

		if (sm[1].str()[0] == '$')
		{
            if (sm[2] == 'H')
			{
				m_group = GROUP_GRBL_HOME;
            }
			else if (sm[2] == 'X')
			{
				m_group = GROUP_GRBL_UNLOCK;
            }
			else if (sm[2] == '?')
			{
				m_group = GROUP_GRBL_STATUS;
            }
			else if (sm[2] == '#')
			{
				m_group = GROUP_GRBL_WCS_INFO;
            }
			else if (sm[2] == 'C')
			{
				m_group = GROUP_GRBL_CHK_MODE;
            }
			else
			{
				m_group = GROUP_GRBL_COMMAND;
            }
		}
		else
		{
			m_group = GROUP_GRBL_SPECIAL;
		}
	}
	else if (m_clean.length() == 0)
	{
		m_type = TYPE_GRBL;
		m_group = GROUP_GRBL_EMPTY;
	}
}