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
	DDLogger::Log("M100::Execute() - BEGIN - args: " + args);
	connection.VerifyConnected();

	// Arg format: G55 X G56 Y G57 Z
	const std::string gIn1 = args.substr(0, 3);
	const std::string axisIn = args.substr(3, 1);
	const std::string gIn2 = args.substr(4, 3);
	const std::string gOut = args.substr(8, 3);
	const std::string axisOut = args.substr(11, 1);
	DDLogger::Log("M100::Execute() - gIn1: " + gIn1 + " " + axisIn + " gIn2: " + gIn2 + " " + axisIn + " gOut: " + gOut + " " + axisOut);

	// Set the pcode for the corresponding G value
	const int pCode = DeterminePCode(gOut);
	DDLogger::Log("M100::Execute() - pCode: " + std::to_string(pCode));

	// Get the 2 points
	const std::vector<Point3> m100points = LoadPoints(connection, gIn1, gIn2);
	DDLogger::Log("M100::Execute() - Points size: " + std::to_string(m100points.size()));

	const std::pair<float, float> points = GetAxisValues(axisIn, m100points);
	DDLogger::Log("M100::Execute() - Axis values: " + std::to_string(points.first) + ", " + std::to_string(points.second));

	// Calculate center value
	char buf[50];
	snprintf(buf, 50, "%.3f", CalcCenterValue(points.first, points.second));
	const std::string centerValueStr = buf;
	DDLogger::Log("M100::Execute() - Center value: " + centerValueStr);

	// Update the output G value
	//std::stringstream ss(std::stringstream::in | std::stringstream::out);
	//ss << "G10 L2 P" << pCode << " " << axisOut << centerValueStr << "\n";
	const std::string output = "G10 L2 P" + std::to_string(pCode) + " " + axisOut + centerValueStr + "\n";//ss.str();

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

	//std::cout << x2 << " + " << "((" << x1 << " - " << x2 << ") div 2) = " << axisCenter << std::endl;

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
		DDLogger::Log("M100::LoadPoints() - gIn1 found: " + point1.wcs + ": " + std::to_string(point1.x) + ", " + std::to_string(point1.y) + ", " + std::to_string(point1.z));
		m100Points.push_back(point1);
	}

	if (points.find(gIn2) != points.end())
	{
		const Point3 point2 = points.find(gIn2)->second;
		DDLogger::Log("M100::LoadPoints() - gIn2 found: " + point2.wcs + ": " + std::to_string(point2.x) + ", " + std::to_string(point2.y) + ", " + std::to_string(point2.z));
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

/*
------------G55XG56XG59X
G54:0.000:0.000:0.000:
G55:-45.048:-42.488:-8.388:
G56:-52.610:0.000:0.000:
G57:0.000:0.000:0.000:
G58:0.000:0.000:0.000:
G59:0.000:0.000:0.000:
G28:0.000:0.000:0.000:
G30:0.000:0.000:0.000:
G92:0.000:0.000:0.000:
[M100 G55 X G56 X G59 X)]
*/

/*void GhostConnection::M100(const string& args) {
	if (!(state & GS_CONNECTED)) { throw GhostException(GhostException::NOT_OPEN); }

	string s, gIn1, gIn2, gOut, axisIn1, axisIn2, axisOut;
	char t;
	string centerValueStr;
	float fval0, fval1;
	stringstream ss(stringstream::in | stringstream::out);
	smatch sm;
	//G55XG56XG59X

		//cout << "------------" << args << endl;
	gIn1 = args.substr(0, 3);
	axisIn1 = args.substr(3, 1);
	gIn2 = args.substr(4, 3);
	axisIn2 = args.substr(7, 1);
	gOut = args.substr(8, 3);
	axisOut = args.substr(11, 1);
	cout << "M100" << endl;
	s = "$#\n";
	writeOS(s.c_str(), s.length());
	Sleep(100);
	m100ErrResult = 0;

	s = "";
	// load the Point class with all the values
	while (readOS(&t, 1) > 0) {
		if (t == '\n') {
			if (s.compare(0, 2, "[G") == 0) {
				if (regex_match(s, sm, RXWCS)) {
					// only save the points of interest
					cout << sm[1] << " :" << stof(sm[2].str()) << " :" << stof(sm[3].str()) << " :" << stof(sm[4].str()) << endl;
					if (sm[1].compare(gIn1) == 0 || sm[1].compare(gIn2) == 0) {
						m100points.push_back(Point3(sm[1], stof(sm[2].str()), stof(sm[3].str()), stof(sm[4].str())));
					}
				}
			}
			s = "";
		}
		else if (t != '\r') {
			s.push_back(t);
		}
	}

	// set the pcode for the corresponding G value
	int pcode = -1;
	if (gOut.compare("G54") == 0)
		pcode = 1;
	else if (gOut.compare("G55") == 0)
		pcode = 2;
	else if (gOut.compare("G56") == 0)
		pcode = 3;
	else if (gOut.compare("G57") == 0)
		pcode = 4;
	else if (gOut.compare("G58") == 0)
		pcode = 5;
	else if (gOut.compare("G59") == 0)
		pcode = 6;

	if (axisIn1 == "X") {
		cout << "X:" << m100points.at(0).wcs << ":" << m100points.at(0).x << " <--> " << m100points.at(1).wcs << ":" << m100points.at(1).x << endl;
		fval0 = m100points.at(0).x;
		fval1 = m100points.at(1).x;
		char buf[50];
		snprintf(buf, 50, "%.3f", calcCenterValue(m100points.at(0).x, m100points.at(1).x));
		centerValueStr = buf;
		//ss << "G10 L2 P" << pcode << " " << axisOut << centerValueStr << "\n";
	}
	else if (axisIn1 == "Y") {
		fval0 = m100points.at(0).y;
		fval1 = m100points.at(1).y;
		cout << "Y:" << m100points.at(0).wcs << ":" << m100points.at(0).y << " <--> " << m100points.at(1).wcs << ":" << m100points.at(1).y << endl;
		char buf[50];
		snprintf(buf, 50, "%.3f", calcCenterValue(m100points.at(0).y, m100points.at(1).y));
		centerValueStr = buf;
		//ss << "G10 L2 P" << pcode << " " << axisOut << centerValueStr << "\n";
	}
	else if (axisIn1 == "Z") {
		fval0 = m100points.at(0).z;
		fval1 = m100points.at(1).z;
		cout << "Z:" << m100points.at(0).wcs << ":" << m100points.at(0).z << " <--> " << m100points.at(1).wcs << ":" << m100points.at(1).z << endl;
		char buf[50];
		snprintf(buf, 50, "%.3f", calcCenterValue(m100points.at(0).z, m100points.at(1).z));
		centerValueStr = buf;
	}
	ss << "G10 L2 P" << pcode << " " << axisOut << centerValueStr << "\n";
	cout << ss.str() << endl;

	// update the output G value
	s = ss.str();

	writeOS(s, s.length());
	Sleep(100);
	s = "";
	while (readOS(&t, 1) > 0) {
		if (t == '\n') {
			s = "";
		}
		else if (t != '\r') {
			s.push_back(t);
		}
	}

	s = "$#\n";
	writeOS(s.c_str(), s.length());
	Sleep(100);

	s = "";
	// get the result and verify within range.
	while (readOS(&t, 1) > 0) {
		if (t == '\n') {
			if (s.compare(0, 2, "[G") == 0) {
				if (regex_match(s, sm, RXWCS)) {
					cout << sm[1] << " :" << sm[2] << " :" << sm[3] << " :" << sm[4] << endl;
					if (sm[1].compare(gOut) == 0) {
						float v1 = fval1 > std::stof(sm[2]) ? fval1 - std::stof(sm[2]) : std::stof(sm[2]) - fval1;
						float v2 = fval1 > fval0 ? fval1 - fval0 : fval0 - fval1;
						//cout << v1 << " : " << v2 << endl;
						if (v1 > v2) {
							m100ErrResult = -1;
						}
					}
				}
			}
			s = "";
		}
		else if (t != '\r') {
			s.push_back(t);
		}
	}
}

//G10 L2 P1 X3.5 Y17.2

float GhostConnection::calcCenterValue(const float x, const float y) {

	float x1 = x > y ? x : y;
	float x2 = x > y ? y : x;


	float axisCenter = x2 + ((x1 - x2) / 2);
	cout << x2 << " + " << "((" << x1 << " - " << x2 << ") div 2) = " << axisCenter << endl;

	return axisCenter;
}
*/