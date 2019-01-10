#include "PointUtility.h"

#include "GhostException.h"

float PointUtility::GetAxisValue(const std::string axis, const Point3& point)
{
	if (axis == "X")
	{
		return point.x;
	}
	else if (axis == "Y")
	{
		return point.y;
	}
	else if (axis == "Z")
	{
		return point.z;
	}

	throw GhostException(GhostException::UNKNOWN_COMMAND, "PointUtility::GetAxisValue() - Invalid axis value: " + axis);
}