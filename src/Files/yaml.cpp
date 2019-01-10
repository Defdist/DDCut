#include "yaml.h"
#include <cstring>

int YAMLObject::TYPEOBJ=0;
int YAMLObject::TYPEFIL=1;
int YAMLObject::TYPERRY=2;
int YAMLObject::TYPELST=3;
int YAMLObject::TYPESTR=4;

std::regex YAMLObject::RXBOF("^---\\s*(#.*)?$");
std::regex YAMLObject::RXEOF("^...\\s*(#.*)?$");
std::regex YAMLObject::RXINDENT("^( *)(.*)$");
std::regex YAMLObject::RXARRAY("^( *)(\\w+):(\\s+(.*))?\\s*$");
std::regex YAMLObject::RXLIST("^( *)- \\s*(.*)\\s*$");
std::regex YAMLObject::RXCOMMENT("^ *(#.*)?\\s*$");
std::regex YAMLObject::RXNEWLINE("\\\\n");


YAMLObject::YAMLObject(const int t, const std::string& s, const size_t l)
	:type(t), value(s), line(l + 1)
{
}

void YAMLObject::addChild(YAMLObject y)
{
	chldrn.push_back(y);
}

YAMLObject& YAMLObject::lastChild()
{
	return chldrn.back();
}

int YAMLObject::getType() const
{
	return type;
}

const std::string& YAMLObject::getValue() const
{
	return value;
}

size_t YAMLObject::getLine() const
{
    return line;
}

const std::vector<YAMLObject>& YAMLObject::getChildren() const
{
	return chldrn;
}

std::vector<YAMLObject> YAMLObject::parseFile(const std::vector<std::string>& vs)
{
    size_t i = 0;
    int parseState = 0;
	std::vector<YAMLObject> ret;
	ret.push_back(YAMLObject(TYPEFIL, "", i));
	for(; i<vs.size(); ++i)
	{
        if (std::regex_match(vs[i], RXCOMMENT))
		{
			continue;
		}

		if (std::regex_match(vs[i], RXBOF))
		{
            if (parseState>0)
			{
                ret.push_back(YAMLObject(TYPEFIL,"",i));
            }
            parseState=1;
            continue;
		}

		if (parseState==2)
		{
			throw YAMLException(YAMLException::PARSE,i);
		}

		if (std::regex_match(vs[i],RXEOF))
		{
            parseState=2;
            continue;
        }

		parse(vs,i,ret.back(),-1);
	}

	return ret;
}

void YAMLObject::parse(const std::vector<std::string>& vs, size_t& i, YAMLObject& parent, int l)
{
	std::smatch sm;
	int type = TYPEOBJ;
	int indent;
	for(; i < vs.size(); ++i)
	{
        if (std::regex_match(vs[i], RXCOMMENT))
		{ 
			continue;
		}
        if (std::regex_match(vs[i], RXBOF))
		{
			break; 
		}
        if (std::regex_match(vs[i], RXEOF))
		{ 
			break; 
		}

		std::regex_match(vs[i], sm, RXINDENT);
		indent = (int)sm[1].length();
        if (indent <= l)
		{ 
			break; 
		}

        if (std::regex_match(vs[i], sm, RXARRAY))
		{
            if (type == TYPEOBJ)
			{
				type = TYPERRY;
			}

            if (type != TYPERRY)
			{
				throw YAMLException(YAMLException::TYPE, i);
			}

            parent.addChild(parseArray(vs[i], i));
            parse(vs, ++i, parent.lastChild(), indent);
            --i;
        }
		else if (std::regex_match(vs[i], sm, RXLIST))
		{
            if (type == TYPEOBJ)
			{
				type = TYPELST;
			}

            if (type != TYPELST)
			{
				throw YAMLException(YAMLException::TYPE, i);
			}

            parent.addChild(parseList(vs[i], i));
            parse(vs, ++i, parent.lastChild(), indent);
            --i;
        }
		else
		{
            throw YAMLException(YAMLException::PARSE,i);
        }
	}
}

YAMLObject YAMLObject::parseArray(const std::string& s,size_t i)
{
	std::smatch sm;
	if (std::regex_match(s, sm, RXARRAY))
	{
		YAMLObject t(TYPERRY, sm[2], i);
		if (sm[4].length() > 0)
		{
			if (!std::regex_match(sm[4].str(), RXCOMMENT))
			{
				t.addChild(parseString(sm[4], i));
			}
		}
		return t;
	}
	else
	{
		throw YAMLException(YAMLException::PARSE, i);
	}
}

YAMLObject YAMLObject::parseList(const std::string& s,size_t i)
{
	std::smatch sm;
	if (std::regex_match(s,sm,RXLIST))
	{
		YAMLObject t(TYPELST, "", i);
		if (sm[2].length() > 0)
		{
			if (std::regex_match(sm[2].str(), RXARRAY))
			{
				t.addChild(parseArray(sm[2], i));
			}
			else if (!std::regex_match(sm[2].str(), RXCOMMENT))
			{
				t.addChild(parseString(sm[2], i));
			}
		}

		return t;
	}
	else
	{
		throw YAMLException(YAMLException::PARSE, i);
	}
}

YAMLObject YAMLObject::parseString(const std::string &s, size_t i)
{
#ifdef _WIN32
    return YAMLObject(TYPESTR, std::regex_replace(s,RXNEWLINE,"\r\n"),i);
#else

    return YAMLObject(TYPESTR,regex_replace(s,RXNEWLINE,"\n"),i);
#endif
}

int YAMLException::PARSE=1;
int YAMLException::TYPE=2;

YAMLException::YAMLException(int t, size_t l)
{
    std::string temp;
	if (t == YAMLException::PARSE)
	{
        temp = "YAML parse error: line " + std::to_string(l + 1);
	}
	else if (t == YAMLException::TYPE)
	{
        temp = "YAML parse error: type mismatch line " + std::to_string(l + 1);
	}
	else
	{
        temp = "YAML error";
	}

	buffer = new char[temp.size()+1];
    strcpy(buffer,temp.c_str());
}

YAMLException::~YAMLException()
{
    if (buffer != nullptr)
	{
        delete[] buffer;
    }
}

const char* YAMLException::what() const noexcept
{
	return buffer;
}
