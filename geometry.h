#ifndef GEOMETRY
#define GEOMETRY
#include "lib.h"
#include "QDPoint.h"
const double  CMP_EPS = 1e-10;
double getLengthXYZ(QDPoint &p1, QDPoint &p2)
{
    double result;
    result = sqrt( (p1.x()-p2.x()) * (p1.x()-p2.x()) +
                   (p1.y()-p2.y()) * (p1.y()-p2.y()) +
                   (p1.z()-p2.z()) * (p1.z()-p2.z()) );

    if(result < CMP_EPS)
        result = 0;
    return result;
}

double getLengthXY(QDPoint &p1, QDPoint &p2)
{
    double result;
    result = sqrt( (p1.x()-p2.x()) * (p1.x()-p2.x()) +
                 (p1.y()-p2.y()) * (p1.y()-p2.y()) );

    if(result < CMP_EPS)
        result = 0;
    return result;
}

double getLengthXZ(QDPoint &p1, QDPoint &p2)
{
    double result;
    result = sqrt( (p1.x()-p2.x()) * (p1.x()-p2.x()) +
                 (p1.z()-p2.z()) * (p1.z()-p2.z()) );

    if(result < CMP_EPS)
        result = 0;
    return result;
}

double getLengthYZ(QDPoint &p1, QDPoint &p2)
{
    double result;
    result = sqrt( (p1.z()-p2.z()) * (p1.z()-p2.z()) +
                 (p1.y()-p2.y()) * (p1.y()-p2.y()) );

    if(result < CMP_EPS)
        result = 0;
    return result;
}

double getLengthX(QDPoint &p1, QDPoint &p2)
{
    double result;
    result = abs(p1.x()-p2.x());

    if(result < CMP_EPS)
        result = 0;
    return result;
}

double getLengthY(QDPoint &p1, QDPoint &p2)
{
    double result;
    result = abs(p1.y()-p2.y());

    if(result < CMP_EPS)
        result = 0;
    return result;
}

double getLengthZ(QDPoint &p1, QDPoint &p2)
{
    double result;
    result = abs(p1.z()-p2.z());

    if(result < CMP_EPS)
        result = 0;
    return result;
}
#endif // GEOMETRY

