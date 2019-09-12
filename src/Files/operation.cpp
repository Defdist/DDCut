#include "operation.h"

#include "yaml.h"
#include "archive.h"
#include "DDException.h"
#include "DDFileManager.h"

#include <DDLogger/DDLogger.h>
#include <Ghost/GhostRegex.h>

Operation::Operation(const YAMLObject& operationYAML)
{
    if (operationYAML.getType() != YAMLObject::TYPELST)
	{
        throw DDException(DDException::BAD_MANIFEST, "not a list of operations | line " + std::to_string(operationYAML.getLine()));
    }

    const std::vector<YAMLObject>& operationYAMLChildren = operationYAML.getChildren();
    if (operationYAMLChildren.size() == 0)
	{
        throw DDException(DDException::BAD_MANIFEST, "operation is empty | line " + std::to_string(operationYAML.getLine()));
    }

    if (operationYAMLChildren[0].getType() != YAMLObject::TYPERRY)
	{
       throw DDException(DDException::BAD_MANIFEST, "operation children must be type array | line " + std::to_string(operationYAML.getLine()));
    }

    for (size_t i = 0; i < operationYAMLChildren.size(); ++i)
	{
        if(operationYAMLChildren[i].getChildren().size() == 0)
		{
            throw DDException(DDException::BAD_MANIFEST, "operation child has no value | line " + std::to_string(operationYAMLChildren[i].getLine()));
        }

        const YAMLObject& child = operationYAMLChildren[i].getChildren()[0];
        if (child.getType() != YAMLObject::TYPESTR)
		{
            throw DDException(DDException::BAD_MANIFEST, "operation values must be type string | line " + std::to_string(child.getLine()));
        }

		const std::string& value = operationYAMLChildren[i].getValue();
        if (value == "pause")
		{
            if (std::regex_match(child.getValue(), Ghost::Regex::RXTRUE))
			{
                m_pause = true;
            }
        }
		else if (value == "reset")
		{
            if (std::regex_match(child.getValue(), Ghost::Regex::RXTRUE))
			{
				m_reset = true;
            }
        }
		else if (value == "timeout")
		{
			m_timeout = stoul(child.getValue());
        }
		else if (value == "step_name")
		{
			m_title = child.getValue();
        }
		else if (value == "step_text")
		{
			m_prompt = child.getValue();
        }
		else if (value == "step_image")
		{
            std::smatch sm;
            std::regex_match(child.getValue(), sm, Ghost::Regex::RXSTRIP);
			m_image = sm[1].str();
        }
		else if (value == "step_gcode")
		{
            std::smatch sm;
            std::regex_match(child.getValue(), sm, Ghost::Regex::RXSTRIP);
			m_file = sm[1].str();
        } 
		else if (value == "if")
		{
			// added if condition to yaml file
			m_hashtable.clear();
            const std::string val = child.getValue();
            std::size_t found = val.find("==");

            if (found != std::string::npos)
			{
				m_hashtable[val.substr(0, found)] = atoi(val.substr(found + 2).c_str());
            }
        }
    }
}

void Operation::Verify(const Archive& archive) const
{
    if (m_file.size() > 0)
	{
		archive.CheckFile(m_file);
    }

    if (m_image.size() > 0)
	{
		archive.CheckFile(m_image);
    }
}

bool Operation::Load()
{	
	if (!m_loaded)
	{
		DDFile* pFile = DDFileManager::GetInstance().GetSelectedFile();
		if (pFile == nullptr)
		{
			DDLogger::Log("Operation::Load - Selected file is null.");
			return false;
		}

		if (!GetFile().empty())
		{
			std::vector<std::string> vs;
			pFile->ReadFile(GetFile(), vs);
			m_gcode.Load(vs);
		}

		if (!GetImage().empty())
		{
			pFile->ReadFile(GetImage(), m_imageBytes);
		}

		m_loaded = true;
	}

	return true;
}


static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

std::string Operation::GetImageBase64() const
{
	unsigned char const* bytes_to_encode = &m_imageBytes[0];
	unsigned int in_len = m_imageBytes.size();

	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
	char_array_3[i++] = *(bytes_to_encode++);
	if (i == 3) {
	  char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
	  char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
	  char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
	  char_array_4[3] = char_array_3[2] & 0x3f;

	  for(i = 0; (i <4) ; i++)
	    ret += base64_chars[char_array_4[i]];
	  i = 0;
	}
	}

	if (i)
	{
	for(j = i; j < 3; j++)
	  char_array_3[j] = '\0';

	char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
	char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
	char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
	char_array_4[3] = char_array_3[2] & 0x3f;

	for (j = 0; (j < i + 1); j++)
	  ret += base64_chars[char_array_4[j]];

	while((i++ < 3))
	  ret += '=';

	}

	return ret;
}