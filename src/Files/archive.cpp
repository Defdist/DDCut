#include "archive.h"

#include "DDException.h"

Archive::Archive(const std::string& path) 
	: m_path(path)
{
}

void Archive::Open()
{
	m_unzFile = unzOpen(m_path.c_str());
	if (m_unzFile == NULL)
	{
		throw DDException(DDException::NOT_FOUND, m_path);
	}
}

void Archive::Close()
{
	unzClose(m_unzFile);
	m_unzFile = NULL;
}

void Archive::ReadFile(const std::string& path, std::vector<std::string>& vs)
{
	if (m_unzFile == NULL)
	{
		throw DDException(DDException::NOT_OPEN);
	}

	if (unzLocateFile(m_unzFile, path.c_str(), (unzFileNameComparer)0) != UNZ_OK)
	{
		throw DDException(DDException::NOT_FOUND_INZ, path);
	}

	if (unzOpenCurrentFile(m_unzFile) != UNZ_OK)
	{
		throw DDException(DDException::NOT_FOUND_INZ, path);
	}

	char buffer[256];
	int readSize;
	std::string line;
	while ((readSize = unzReadCurrentFile(m_unzFile, buffer, 256)) > 0)
	{
		for (int i = 0; i < readSize; ++i)
		{
			if (buffer[i] == '\n')
			{
                vs.push_back(line);
				line = "";
			}
			else if (buffer[i] != '\r')
			{
				line.push_back(buffer[i]);
			}
		}
	}

	if (line.length() > 0)
	{
		vs.push_back(line);
		line = "";
	}

	unzCloseCurrentFile(m_unzFile);
}

void Archive::ReadFile(const std::string& path, std::vector<unsigned char>& vuc)
{
	if (m_unzFile == NULL)
	{
		throw DDException(DDException::NOT_OPEN);
	}

	if (unzLocateFile(m_unzFile, path.c_str(), (unzFileNameComparer)0) != UNZ_OK)
	{
		throw DDException(DDException::NOT_FOUND_INZ, path);
	}

	if (unzOpenCurrentFile(m_unzFile) != UNZ_OK)
	{
		throw DDException(DDException::NOT_FOUND_INZ, path);
	}

	unsigned char buffer[256];
	int readSize;
	while ((readSize = unzReadCurrentFile(m_unzFile, &buffer, 256)) > 0)
	{
		for (int i=0; i < readSize; ++i)
		{
            vuc.push_back(buffer[i]);
		}
	}

	unzCloseCurrentFile(m_unzFile);
}
void Archive::CheckFile(const std::string& path) const
{
    if (m_unzFile == NULL)
	{
        throw DDException(DDException::NOT_OPEN);
    }

    if (unzLocateFile(m_unzFile, path.c_str(), (unzFileNameComparer)0) != UNZ_OK)
	{
        throw DDException(DDException::NOT_FOUND_INZ, path);
    }
}

std::vector<std::string> Archive::ListFiles()
{
    if (m_unzFile == NULL)
	{
        throw DDException(DDException::NOT_OPEN);
    }

	std::vector<std::string> ret;
    if (unzGoToFirstFile(m_unzFile) == UNZ_OK)
	{
        char buffer[256];
        do
		{
            unzGetCurrentFileInfo(m_unzFile, NULL, buffer, 256, NULL, 0, NULL, 0);
            ret.push_back(buffer);
        } while (unzGoToNextFile(m_unzFile) == UNZ_OK);
    }

    return ret;
}
