#pragma once

#include "GCodeFile.h"

#include <string>
#include <regex>
#include <vector>
#include <map>

// Forward Declarations
class Archive;
class YAMLObject;

typedef void* HANDLE;

/*
 * Represents an operation from a YAML manifest
 * Lazily loads image data and GCodeFile from zip file.
 */
class Operation
{
private:
	bool m_pause = false;
	bool m_reset = false;
	bool m_loaded = false;
	unsigned int m_timeout = 0;

	std::string m_title;
	std::string m_prompt;
	std::string m_image;
	std::string m_file;

	std::map<std::string, int> m_hashtable; // TODO: Determine better name

	std::vector<unsigned char> m_imageBytes;

	GCodeFile m_gcode;

public:
	bool Load();

	Operation() = default;
	Operation(const YAMLObject& operationYAML);
	void Verify(const Archive& archive) const;

	// GETTERS
	inline bool GetPause() const { return m_pause; }
	inline bool GetReset() const { return m_reset; }
	inline bool IsLoaded() const { return m_loaded; }
	inline unsigned int GetTimeout() const { return m_timeout; }

	inline const std::string& GetTitle() const { return m_title; }
	inline const std::string& GetPrompt() const { return m_prompt; }
	inline const std::string& GetImage() const { return m_image; }
	inline const std::string& GetFile() const { return m_file; }

	inline const std::map<std::string, int>& GetHashtable() const { return m_hashtable; }

	inline const std::vector<unsigned char>& GetImageBytes() const { return m_imageBytes; }
	std::string GetImageBase64() const;

	inline bool HasGCodes() const { return !m_file.empty(); }
	inline const GCodeFile& GetGCodeFile() const { return m_gcode; }

	static std::regex RXBMP;
	static std::regex RXJPEG;
};