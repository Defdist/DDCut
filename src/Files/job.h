#pragma once

#include <string>
#include <vector>

#include "yaml.h"
#include "operation.h"

// TODO: Create a JobFactory, and make this a trivial data object?

/*
 * This class handles a job from the manifest.
 * A job consists of information acquired from the manifest yaml file.
 * This includes a title, a prompt, a vector of Operations, a vector of strings that are filenames of guides, a vector of strings that are filenames of models, and a minimum firmware version.
 */
class Job
{
	void SetGuides(const YAMLObject& y);
	void SetModels(const YAMLObject& y);
	void SetOperations(const YAMLObject& y);

	std::string m_title;
	std::string m_prompt;
	std::string m_minimumFirmwareVersion;
	std::vector<std::string> m_guides;
	std::vector<std::string> m_models;
	std::vector<Operation> m_operations;

public:
    Job() = default;
	Job(const YAMLObject& jobYAML);// Constructor that takes a YAMLObject and parses it

	void Verify(const Archive& archive) const;

	// GETTERS
	inline const std::string& GetTitle() const { return m_title; }
	inline const std::string& GetPrompt() const { return m_prompt; }
	inline const std::string& GetMinFirmwareVersion() const { return m_minimumFirmwareVersion; }

	inline const std::vector<Operation>& GetOperations() const { return m_operations; }
	inline Operation& GetOperation(const size_t index) { return m_operations[index]; }

	inline const std::vector<std::string>& GetGuides() const { return m_guides; }
	inline const std::string& GetGuide(const size_t index) const { return m_guides[index]; }

	inline const std::vector<std::string>& GetModels() const { return m_models; }
	inline const std::string& GetModel(const size_t index) const { return m_models[index]; }
};