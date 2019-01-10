#include "DDException.h"

#include <cstring>

DDException::DDException(const EExceptionType t)
	: m_type(t)
{

}

DDException::DDException(const EExceptionType t, const std::string& s)
	: m_type(t)
{
	std::string temp;
    if (m_type == NOT_FOUND)
	{
        temp = "File not found: " + s;
    }
	else if (m_type == NOT_FOUND_INZ)
	{
        temp = "File not found in archive: " + s;
    }
	else if (m_type == BAD_MANIFEST)
	{
        temp = "Bad manifest: " + s;
    }
	else if (m_type == NOT_OPEN)
	{
        temp = "File was not open";
    }
	else
	{
        temp = "DD archive error";
    }

    buffer = new char[temp.size() + 1];
    strcpy(buffer, temp.c_str());
}

DDException::~DDException()
{
    if (buffer != nullptr)
	{
        delete[] buffer;
    }
}

const char* DDException::what() const noexcept
{
    return buffer;
}

DDException::EExceptionType DDException::GetType()
{
	return m_type;
}
