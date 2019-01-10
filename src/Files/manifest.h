#pragma once

#include "job.h"

#include <string>
#include <vector>
#include <map>

/*
 * Manifest represents a YAML manifest file as a vector of Jobs, as well as providing a map for translating from job name to index.
 */
class Manifest
{
private:
	std::vector<Job> m_jobs;
	std::map<std::string, size_t> m_jobIndex;

public:
	Manifest() = default;

	void LoadManifest(const std::vector<std::string>& ls);
	void Verify(const Archive& archive) const;

	inline const std::vector<Job>& GetJobs() const { return m_jobs; }
	inline Job& GetJob(const std::string& jobName) { return m_jobs[m_jobIndex[jobName]]; }
};
