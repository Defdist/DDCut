#pragma once

#include "Point.h"

#include <Common/OSFile.h>
#include <string>
#include <vector>
#include <utility>

// Forward Declarations
class GhostConnection;

class M100
{
public:
	void Execute(const GhostConnection& connection, const std::string& args) const;

private:
	float CalcCenterValue(const float x, const float y) const;
	int DeterminePCode(const std::string& gCode) const;

	std::vector<Point3> LoadPoints(const GhostConnection& connection, const std::string& gIn1, const std::string& gIn2) const;
	std::pair<float, float> GetAxisValues(const std::string& axisIn, const std::vector<Point3>& m100points) const;

	void VerifyRange(const GhostConnection& connection, const float fval0, const float fval1, const std::string& gOut, const std::string& axisOut) const;
};