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

QDPoint &QDPoint::operator =(QDPoint &point_2)
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

