#pragma once

#include <exception>
#include <string>

/*
Exception class for DD file specific things
NOT_FOUND for when a DD file isn't found
NOT_FOUND_INZ for when a requested file isn't found in the DD file
NOT_OPEN for when a DD file isn't open and an operation is attempted
BAD_MANIFEST for when the manifest is improperly written
*/
class DDException : public std::exception
{
public:
	enum EExceptionType
	{
		NOT_FOUND,
		NOT_FOUND_INZ,
		NOT_OPEN,
		BAD_MANIFEST
	};

public:
	DDException(const EExceptionType t);
	DDException(const EExceptionType t, const std::string& s);
	~DDException();

	const char* what() const noexcept;
	EExceptionType GetType();

private:
	EExceptionType m_type;
	char* buffer = nullptr;
};