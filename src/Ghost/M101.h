#pragma once

#include "Point.h"

#include <string>
#include <vector>

// Forward Declarations
class GhostConnection;

class M101
{
public:
	void Execute(GhostConnection& connection, const std::string& args) const;

private:
	std::vector<float> LoadAxisValues(GhostConnection& connection, const std::string& gIn1, const std::string& gIn2, const std::string& gIn3, const std::string& axis) const;

	bool CheckTolerance(const std::vector<float>& pointValues, const std::string& axis, const float maxTolerance) const;
};