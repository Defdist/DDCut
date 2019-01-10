#ifndef COORDINATE_H_INCLUDED
#define COORDINATE_H_INCLUDED

class Coordinate
{
public:
    float X_absolute_prior_to_probe;
    float Y_absolute_prior_to_probe;
    float Z_absolute_prior_to_probe;
    Coordinate(float fx,float fy,float fz);
    Coordinate& operator=(const Coordinate& p);
    Coordinate operator+(const Coordinate& p);
    Coordinate operator-(const Coordinate& p);
};


#endif
