#include "DDFileManager.h"

DDFileManager& DDFileManager::GetInstance()
{
	static DDFileManager instance;
	return instance;
}

void DDFileManager::SetSelectedFile(DDFile* ddFile)
{
	delete m_selectedFile;
	m_selectedFile = ddFile;
}

void DDFileManager::SetSelectedFile(const std::string& ddFilePath)
{
	delete m_selectedFile;
	m_selectedFile = new DDFile(ddFilePath);
}