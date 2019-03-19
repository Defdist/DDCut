#include "M101.h"

#include "GhostConstants.h"
#include "GhostRegex.h"
#include "GhostException.h"
#include "Common/OSUtility.h"
#include "DDLogger/DDLogger.h"
#include "Common/OSFile.h"
#include "GhostConnection.h"
#include "PointUtility.h"

#include <vector>
#include <iostream>

/*
[G54:0.000,0.000,0.000]
[G55:-32.013,-71.345,-42.408]
[G56:0.000,0.000,0.000]
[G57:0.000,0.000,0.000]
[G58:0.000,0.000,0.000]
[G59:0.000,0.000,0.000]
[G28:0.000,0.000,0.000]
[G30:0.000,0.000,0.000]
[G92:0.000,0.000,0.000]
[TLO:0.000]
[PRB:-32.013,-74.548,-49.408:1]
*/
// TODO: Document args format.
void M101::Execute(GhostConnection& connection, const std::string& args) const
{
	DDLogger::Log("M101::Execute() - BEGIN - args:" + args);
	connection.VerifyConnected();
	
	// Unpack args.
	const std::string gIn1 = args.substr(0, 3);
	const std::string gIn2 = args.substr(3, 3);
	const std::string gIn3 = args.substr(6, 3);
	const std::string axis = args.substr(9, 1);
	const float maxTolerance = std::stof(args.substr(10));

	// Get points.
	const std::vector<float> m101PointAxisValues = LoadAxisValues(connection, gIn1, gIn2, gIn3, axis);
	
	// Check tolerance.
	if (!CheckTolerance(m101PointAxisValues, axis, maxTolerance))
	{
		throw GhostException(GhostException::M101_FAIL, axis);
	}

	DDLogger::Log("M101::Execute() - END");
}

std::vector<float> M101::LoadAxisValues(GhostConnection& connection, const std::string& gIn1, const std::string& gIn2, const std::string& gIn3, const std::string& axis) const
{
	std::vector<float> m101PointAxisValues;

	const std::map<std::string, Point3> points = connection.GetPoints();
	if (points.find(gIn1) != points.end())
	{
		const Point3 point1 = points.find(gIn1)->second;
		DDLogger::Log("M101::LoadPoints() - gIn1 found -" + point1.wcs + ": " + std::to_string(point1.x) + ", " + std::to_string(point1.y) + ", " + std::to_string(point1.z));

		m101PointAxisValues.push_back(PointUtility::GetAxisValue(axis, point1));
	}

	if (points.find(gIn2) != points.end())
	{
		const Point3 point2 = points.find(gIn2)->second;
		DDLogger::Log("M101::LoadPoints() - gIn2 found -" + point2.wcs + ": " + std::to_string(point2.x) + ", " + std::to_string(point2.y) + ", " + std::to_string(point2.z));

		m101PointAxisValues.push_back(PointUtility::GetAxisValue(axis, point2));
	}

	if (points.find(gIn3) != points.end())
	{
		const Point3 point3 = points.find(gIn3)->second;
		DDLogger::Log("M101::LoadPoints() - gIn3 found -" + point3.wcs + ": " + std::to_string(point3.x) + ", " + std::to_string(point3.y) + ", " + std::to_string(point3.z));

		m101PointAxisValues.push_back(PointUtility::GetAxisValue(axis, point3));
	}

	return m101PointAxisValues;
}

bool M101::CheckTolerance(const std::vector<float>& pointValues, const std::string& axis, const float maxTolerance) const
{
	auto mmax = max_element(std::begin(pointValues), std::end(pointValues));
	auto mmin = min_element(std::begin(pointValues), std::end(pointValues));
	DDLogger::Log("M101::CheckTolerance() - " + axis + " - Max:" + std::to_string(*mmax) + " Min:" + std::to_string(*mmin) + " Diff:" + std::to_string(std::abs(*mmax - *mmin)));

	if (std::abs(*mmax - *mmin) >= maxTolerance)
	{
		return false;
	}

	return true;
}