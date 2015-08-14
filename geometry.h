#ifndef GEOMETRY
#define GEOMETRY
#include "lib.h"
#include "QDPoint.h"

double getLength3(QDPoint p1, QDPoint p2)
{
    return sqrt( (p1.x()-p2.x()) * (p1.x()-p2.x()) +
                 (p1.y()-p2.y()) * (p1.y()-p2.y()) +
                 (p1.z()-p2.z()) * (p1.z()-p2.z()) );
}

double getLengthXY(QDPoint p1, QDPoint p2)
{
    return sqrt( (p1.x()-p2.x()) * (p1.x()-p2.x()) +
                 (p1.y()-p2.y()) * (p1.y()-p2.y()) );
}

double getLengthX(QDPoint p1, QDPoint p2)
{
    return abs(p1.x()-p2.x());
}

double getLengthY(QDPoint p1, QDPoint p2)
{
    return abs(p1.y()-p2.y());
}

double getLengthZ(QDPoint p1, QDPoint p2)
{
    return abs(p1.z()-p2.z());
}
#endif // GEOMETRY

