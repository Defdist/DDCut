#pragma once

#include <string>

class Point3
{
public:
	Point3() = default;
	Point3(const std::string& pwcs, const float fx, const float fy, const float fz);
	Point3& operator=(const Point3& p);
	Point3 operator+(const Point3& p);
	Point3 operator-(const Point3& p);


    std::string wcs;
    float x;
    float y;
    float z;
};
