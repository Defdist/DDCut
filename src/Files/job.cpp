#include "job.h"
#include "DDException.h"

#include <Ghost/GhostRegex.h>

Job::Job(const YAMLObject& jobYAML)
{
	if (jobYAML.getType() != YAMLObject::TYPELST)
	{
        throw DDException(DDException::BAD_MANIFEST, "not a list of jobs | line " + std::to_string(jobYAML.getLine()));
	}

    const std::vector<YAMLObject>& children = jobYAML.getChildren();

    if (children.size() == 0)
	{
        throw DDException(DDException::BAD_MANIFEST, "job list entry is empty | line " + std::to_string(jobYAML.getLine()));
    }

    if (children[0].getType() != YAMLObject::TYPERRY)
	{
        throw DDException(DDException::BAD_MANIFEST, "job values must be type array | line " + std::to_string(jobYAML.getLine()));
    }

    for (size_t i=0; i < children.size(); ++i)
	{
        if (children[i].getChildren().size() > 0)
		{
            const YAMLObject& child = children[i].getChildren()[0];
			const std::string& value = children[i].getValue();
            if (value == "job_name")
			{
				m_title = child.getValue();
            }
			else if (value == "job_text")
			{
				m_prompt = child.getValue();
            }
			else if (value == "job_steps")
			{
                SetOperations(children[i]);
            }
			else if (value == "guide_files")
			{
                SetGuides(children[i]);
            }
			else if (value == "model_files")
			{
                SetModels(children[i]);
            }
			else if (value == "min_fw_version")
			{
				m_minimumFirmwareVersion = child.getValue();
            }
        }
    }
}

void Job::Verify(const Archive& a) const
{
    for (size_t i=0; i < m_operations.size(); ++i)
	{
		m_operations[i].Verify(a);
    }
}

void Job::SetOperations(const YAMLObject& y)
{
	std::vector<YAMLObject> t = y.getChildren();

	for(unsigned int i = 0; i < t.size(); ++i)
	{
		m_operations.push_back(Operation(t[i]));
	}
}

void Job::SetGuides(const YAMLObject& y)
{
	std::vector<YAMLObject> t = y.getChildren();
	std::smatch sm;

	for (size_t i = 0; i < t.size(); ++i)
	{
		if (t[i].getType() == YAMLObject::TYPELST)
		{
            std::regex_match(t[i].lastChild().getValue(), sm, Ghost::Regex::RXSTRIP);
			m_guides.push_back(sm[1].str());
		}
	}
}

void Job::SetModels(const YAMLObject& y)
{
	std::vector<YAMLObject> t = y.getChildren();
	std::smatch sm;
	for (size_t i = 0; i < t.size(); ++i)
	{
		if (t[i].getType() == YAMLObject::TYPELST)
		{
            std::regex_match(t[i].lastChild().getValue(), sm, Ghost::Regex::RXSTRIP);
			m_models.push_back(sm[1].str());
		}
	}
}
