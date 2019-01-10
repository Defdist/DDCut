#include "DDFile.h"

#include <Common/FileUtility.h>

DDFile::DDFile(const std::string& path) 
	: m_archive(path)
{
	m_archive.Open();
	std::vector<std::string> vs;
	m_archive.ReadFile("manifest.yml", vs);
	m_manifest.LoadManifest(vs);
	m_manifest.Verify(m_archive);
	m_archive.Close();
}

Job& DDFile::GetJob(const std::string& jobName)
{
    return m_manifest.GetJob(jobName);
}

const std::vector<Job>& DDFile::GetJobs()
{
	return m_manifest.GetJobs();
}

void DDFile::ReadFile(const std::string& path, std::vector<unsigned char>& vuc)
{
    m_archive.Open();
    m_archive.ReadFile(path, vuc);
    m_archive.Close();
}

void DDFile::ReadFile(const std::string& path, std::vector<std::string>& vs)
{
    m_archive.Open();
    m_archive.ReadFile(path, vs);
    m_archive.Close();
}

void DDFile::SaveFileInternal(const std::string& file, const std::string& path)
{
	std::vector<unsigned char> vuc;
    m_archive.ReadFile(file, vuc);

    if (FileUtility::MakeDirectory(path, file))
	{
		FileUtility::WriteFile(path + file, vuc);
    }
}

void DDFile::SaveFiles(const std::vector<std::string>& files, const std::string& path)
{
	m_archive.Open();

	for (size_t i = 0; i < files.size(); ++i)
	{
        SaveFileInternal(files[i], path);
	}

	m_archive.Close();
}

std::vector<std::string> DDFile::ListFiles()
{
    m_archive.Open();
	const std::vector<std::string> files = m_archive.ListFiles();
    m_archive.Close();

    return files;
}
