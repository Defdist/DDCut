#pragma once

#include <string>

struct FirmwareVersion
{
	const std::string grblVersion;
	const std::string ddVersion;

	FirmwareVersion(const std::string& grbl, const std::string& dd)
		: grblVersion(grbl), ddVersion(dd)
	{

	}
};