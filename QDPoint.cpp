#include "QDPoint.h"

QDPoint::QDPoint()
{
    px = 0;
    py = 0;
    pz = 0;
}

QDPoint::QDPoint(double xpos, double ypos, double zpos)
{
    px = xpos;
    py = ypos;
    pz = zpos;
}

QDPoint &QDPoint::operator =(const QDPoint &point_2)
{
    px = point_2.x();
    py = point_2.y();
    pz = point_2.z();
    return *this;
}

QTextStream& operator <<(QTextStream &out, const QDPoint& p)
{
    out << qSetRealNumberPrecision(10) << p.x()<< " " << qSetRealNumberPrecision(10) << p.y()<< " " << qSetRealNumberPrecision(10) << p.z();
    return out;
}

double QDPoint::x()const
{
    return px;
}

double QDPoint::y()const
{
    return py;
}

double QDPoint::z()const
{
    return pz;
}

double &QDPoint::rx()
{
    return px;
}

double &QDPoint::ry()
{
    return py;
}

double &QDPoint::rz()
{
    return pz;
}

void QDPoint::setX(double x)
{
    px = x;
}

void QDPoint::setY(double y)
{
    py = y;
}

void QDPoint::setZ(double z)
{
    pz = z;
}

bool QDPoint::compareX(const QDPoint &p2)
{
    if(fabs(this->x() - p2.x()) < CMP_EPS)
        return true;
    else
        return false;
}

bool QDPoint::compareY(const QDPoint &p2)
{
    if(fabs(this->y() - p2.y()) < CMP_EPS)
        return true;
    else
        return false;
}

bool QDPoint::compareZ(const QDPoint &p2)
{
    if(fabs(this->z() - p2.z()) < CMP_EPS)
        return true;
    else
        return false;
}

