#pragma once

#include "DDFile.h"

#include <string>

class DDFileManager
{
public:
	static DDFileManager& GetInstance();

	void SetSelectedFile(DDFile* ddFile);
	void SetSelectedFile(const std::string& ddFilePath);

	inline DDFile* GetSelectedFile() const { return m_selectedFile; }

private:
	DDFileManager() = default;

    DDFile* m_selectedFile;
};