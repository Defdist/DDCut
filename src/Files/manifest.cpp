#include "manifest.h"

#include "yaml.h"
#include "DDException.h"

void Manifest::LoadManifest(const std::vector<std::string>& ls)
{
	const std::vector<YAMLObject> files = YAMLObject::parseFile(ls);
    if (files.size() > 0)
	{
        const std::vector<YAMLObject>& children = files[0].getChildren();
        for (size_t i = 0; i < children.size(); ++i)
		{
            Job j(children[i]);
            m_jobIndex[j.GetTitle()] = m_jobs.size();
			m_jobs.push_back(j);
        }
    }
	else
	{
        throw DDException(DDException::BAD_MANIFEST, "empty manifest");
    }
}

void Manifest::Verify(const Archive& archive) const
{
    for (size_t i = 0; i < m_jobs.size(); ++i)
	{
		m_jobs[i].Verify(archive);
    }
}