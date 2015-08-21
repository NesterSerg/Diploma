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
    result = fabs(p1.x()- p2.x());

    if(result < CMP_EPS)
        result = 0;
    return result;
}

double getLengthY(QDPoint &p1, QDPoint &p2)
{
    double result;
    result = fabs(p1.y()- p2.y());

    if(result < CMP_EPS)
        result = 0;
    return result;
}

double getLengthZ(QDPoint &p1, QDPoint &p2)
{
    double result;
    result = fabs(p1.z()- p2.z());

    if(result < CMP_EPS)
        result = 0;
    return result;
}

double cosXY(QDPoint &center, QDPoint &p1, QDPoint &p2)
{
    double cos_phi;
    cos_phi = getLengthXY(center, p1) * getLengthXY(center, p1);
    cos_phi += getLengthXY(center, p2) * getLengthXY(center, p2);
    cos_phi -= getLengthXY(p1, p2) * getLengthXY(p1, p2);
    cos_phi /= 2 * getLengthXY(center, p1) * getLengthXY(center, p2);

    return cos_phi;
}

double cosXZ(QDPoint &center, QDPoint &p1, QDPoint &p2)
{
    double cos_phi;
    cos_phi = getLengthXZ(center, p1) * getLengthXZ(center, p1);
    cos_phi += getLengthXZ(center, p2) * getLengthXZ(center, p2);
    cos_phi -= getLengthXZ(p1, p2) * getLengthXZ(p1, p2);
    cos_phi /= 2 * getLengthXZ(center, p1) * getLengthXZ(center, p2);

    return cos_phi;
}

double cosYZ(QDPoint &center, QDPoint &p1, QDPoint &p2)
{
    double cos_phi;
    cos_phi = getLengthYZ(center, p1) * getLengthYZ(center, p1);
    cos_phi += getLengthYZ(center, p2) * getLengthYZ(center, p2);
    cos_phi -= getLengthYZ(p1, p2) * getLengthYZ(p1, p2);
    cos_phi /= 2 * getLengthYZ(center, p1) * getLengthYZ(center, p2);

    return cos_phi;
}

int placeOfPointXY(QDPoint &p1, QDPoint &p2, QDPoint &p)
{
    if( (p1.y()-p2.y()) * p.x() + (p2.x() - p1.x()) * p.y() + (p1.x() * p2.y() - p2.x() * p1.y()) < 0)
        return -1;
    else
        return 1;
}

int placeOfPointXZ(QDPoint &p1, QDPoint &p2, QDPoint &p)
{
    if( (p1.z()-p2.z()) * p.x() + (p2.x() - p1.x()) * p.z() + (p1.x() * p2.z() - p2.x() * p1.z()) < 0)
        return -1;
    else
        return 1;
}

int placeOfPointYZ(QDPoint &p1, QDPoint &p2, QDPoint &p)
{
    if( (p1.y()-p2.y()) * p.z() + (p2.z() - p1.z()) * p.y() + (p1.z() * p2.y() - p2.z() * p1.y()) < 0)
        return -1;
    else
        return 1;
}

bool checkPlaneX(QDPoint &p1, QDPoint &p2)
{
    if(fabs(p1.x() - p2.x()) < CMP_EPS)
        return true;
    else
        return false;
}

bool checkPlaneY(QDPoint &p1, QDPoint &p2)
{
    if(fabs(p1.y() - p2.y()) < CMP_EPS)
        return true;
    else
        return false;
}

bool checkPlaneZ(QDPoint &p1, QDPoint &p2)
{
    if(fabs(p1.z() - p2.z()) < CMP_EPS)
        return true;
    else
        return false;
}
#endif // GEOMETRY

