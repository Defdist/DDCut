#include "coordinate.h"

Coordinate::Coordinate(float fx,float fy, float fz)
{
    X_absolute_prior_to_probe = fx;
    Y_absolute_prior_to_probe = fy;
    Z_absolute_prior_to_probe = fz;

}

Coordinate& Coordinate::operator=(const Coordinate& p)
{
    X_absolute_prior_to_probe = p.X_absolute_prior_to_probe;
    Y_absolute_prior_to_probe = p.Y_absolute_prior_to_probe;
    Z_absolute_prior_to_probe = p.Z_absolute_prior_to_probe;
    return *this;
}

Coordinate Coordinate::operator+(const Coordinate& p)
{
    return Coordinate(
		X_absolute_prior_to_probe + p.X_absolute_prior_to_probe,
		Y_absolute_prior_to_probe + p.Y_absolute_prior_to_probe,
		Z_absolute_prior_to_probe + p.Z_absolute_prior_to_probe
	);
}

Coordinate Coordinate::operator-(const Coordinate& p)
{
    return Coordinate(
		X_absolute_prior_to_probe - p.X_absolute_prior_to_probe, 
		Y_absolute_prior_to_probe - p.Y_absolute_prior_to_probe, 
		Z_absolute_prior_to_probe - p.Z_absolute_prior_to_probe
	);
}
