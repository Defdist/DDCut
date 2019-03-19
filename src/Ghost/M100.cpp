#include "M100.h"

#include "GhostConstants.h"
#include "GhostRegex.h"
#include "GhostException.h"
#include "Point.h"
#include "Common/OSUtility.h"
#include "DDLogger/DDLogger.h"
#include "GhostConnection.h"
#include "PointUtility.h"

#include <regex>
#include <sstream>
#include <iostream>

// Command: M100 Gaa U Gbb V Gcc W
// Example : M100 G55 X G56 X G59 X
// Name : Find midpoint and store to WCS
// Summary : (Supported in DDcut Only) Find the midpoint between WCS Gaa's U axis and WCS Gbb's V axis, then store result in WCS Gcc's W axis.
//
// Changes an axis value of a coordinate system to the midpoint of 2 other coordinate systems.
// The example would set the G59 coordinate system's X axis value to be equal to the midpoint of G55's X axis and G56's X axis.
// Example command that would be sent to GG to update the coordinate system's axis value: G10 L2 P1 X3.5 Y17.2
void M100::Execute(const GhostConnection& connection, const std::string& args) const
{
	DDLogger::Log("M100::Execute() - BEGIN - args:" + args);
	connection.VerifyConnected();

	// Arg format: G55 X G56 Y G57 Z
	const std::string gIn1 = args.substr(0, 3);
	const std::string axisIn = args.substr(3, 1);
	const std::string gIn2 = args.substr(4, 3);
	const std::string gOut = args.substr(8, 3);
	const std::string axisOut = args.substr(11, 1);

	// Set the pcode for the corresponding G value
	const int pCode = DeterminePCode(gOut);

	// Get the 2 points
	const std::vector<Point3> m100points = LoadPoints(connection, gIn1, gIn2);
	const std::pair<float, float> points = GetAxisValues(axisIn, m100points);

	// Calculate center value
	char buf[50];
	snprintf(buf, 50, "%.3f", CalcCenterValue(points.first, points.second));
	const std::string centerValueStr = buf;

	// Update the output G value
	std::stringstream ss(std::stringstream::in | std::stringstream::out);
	ss << "G10 L2 P" << pCode << " " << axisOut << centerValueStr << "\n";
	const std::string output = ss.str();

	DDLogger::Log("M100::Execute() - " + output);
	connection.WriteWithTimeout(output, 100);
	connection.flushReads();

	// Check that new point system has correct values.
	VerifyRange(connection, points.first, points.second, gOut, axisOut);

	DDLogger::Log("M100::Execute() - END");
}

float M100::CalcCenterValue(const float x, const float y) const
{
	const float x1 = x > y ? x : y;
	const float x2 = x > y ? y : x;

	const float axisCenter = x2 + ((x1 - x2) / 2);

	DDLogger::Log("M100::CalcCenterValue() - x: " + std::to_string(x) + " y: " + std::to_string(y) + " center: " + std::to_string(axisCenter));
	std::cout << x2 << " + " << "((" << x1 << " - " << x2 << ") div 2) = " << axisCenter << std::endl;

	return axisCenter;
}

int M100::DeterminePCode(const std::string& gCode) const
{
	if (gCode.compare("G54") == 0)
	{
		return 1;
	}
	else if (gCode.compare("G55") == 0)
	{
		return 2;
	}
	else if (gCode.compare("G56") == 0)
	{
		return 3;
	}
	else if (gCode.compare("G57") == 0)
	{
		return 4;
	}
	else if (gCode.compare("G58") == 0)
	{
		return 5;
	}
	else if (gCode.compare("G59") == 0)
	{
		return 6;
	}

	return -1;
}

std::vector<Point3> M100::LoadPoints(const GhostConnection& connection, const std::string& gIn1, const std::string& gIn2) const
{
	std::vector<Point3> m100Points;

	const std::map<std::string, Point3> points = connection.GetPoints();
	if (points.find(gIn1) != points.end())
	{
		const Point3 point1 = points.find(gIn1)->second;
		DDLogger::Log("M100::LoadPoints() - gIn1 found -" + point1.wcs + ": " + std::to_string(point1.x) + ", " + std::to_string(point1.y) + ", " + std::to_string(point1.z));
		m100Points.push_back(point1);
	}

	if (points.find(gIn2) != points.end())
	{
		const Point3 point2 = points.find(gIn2)->second;
		DDLogger::Log("M100::LoadPoints() - gIn2 found -" + point2.wcs + ": " + std::to_string(point2.x) + ", " + std::to_string(point2.y) + ", " + std::to_string(point2.z));
		m100Points.push_back(point2);
	}

	return m100Points;
}

std::pair<float, float> M100::GetAxisValues(const std::string& axisIn, const std::vector<Point3>& m100points) const
{
	float fval0, fval1;
	if (axisIn == "X")
	{
		fval0 = m100points.at(0).x;
		fval1 = m100points.at(1).x;
	}
	else if (axisIn == "Y")
	{
		fval0 = m100points.at(0).y;
		fval1 = m100points.at(1).y;
	}
	else if (axisIn == "Z")
	{
		fval0 = m100points.at(0).z;
		fval1 = m100points.at(1).z;
	}

	DDLogger::Log("M100::GetPoints() - " + axisIn + " axis - " + m100points.at(0).wcs + ":" + std::to_string(fval0) + " <--> " + m100points.at(1).wcs + ":" + std::to_string(fval1));

	return std::make_pair(fval0, fval1);
}

void M100::VerifyRange(const GhostConnection& connection, const float fval0, const float fval1, const std::string& gOut, const std::string& axisOut) const
{
	const std::map<std::string, Point3> points = connection.GetPoints();
	if (points.find(gOut) != points.end())
	{
		const Point3 point = points.find(gOut)->second;
		DDLogger::Log("M100::GetResultAndVerifyRange() - gOut found -" + point.wcs + ": " + std::to_string(point.x) + ", " + std::to_string(point.y) + ", " + std::to_string(point.z));

		const float axisValue = PointUtility::GetAxisValue(axisOut, point);
		const float v1 = fval1 > axisValue ? fval1 - axisValue : axisValue - fval1;
		const float v2 = fval1 > fval0 ? fval1 - fval0 : fval0 - fval1;

		if (v1 > v2)
		{
			DDLogger::Log("M100::GetVerifyRange() - Value not in range. Value: " + std::to_string(point.x) + " - Range: " + std::to_string(fval0) + "-" + std::to_string(fval1));
			throw GhostException(GhostException::M100_OUTOFRANGE);
		}
	}
	else
	{
		DDLogger::Log("M100::VerifyRange() - " + gOut + " NOT FOUND.");
	}
}