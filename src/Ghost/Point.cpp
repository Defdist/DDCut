#include "Point.h"

Point3::Point3(const std::string& pwcs, const float fx, const float fy, const float fz)
{
    wcs = pwcs;
    x = fx;
    y = fy;
    z = fz;
}

Point3& Point3::operator=(const Point3& p)
{
    wcs = p.wcs;
    x = p.x;
    y = p.y;
    z = p.z;

    return *this;
}

Point3 Point3::operator+(const Point3& p)
{
    return Point3(wcs,x+p.x,y+p.y,z+p.z);
}

Point3 Point3::operator-(const Point3& p)
{
    return Point3(p.wcs,x-p.x,y-p.y,z-p.z);
}
