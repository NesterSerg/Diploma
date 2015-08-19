#ifndef QDPOINT_H
#define QDPOINT_H
//#include <QTextStream>

#include "lib.h"
class QDPoint
{
    public:
        QDPoint();
        QDPoint(double xpos, double ypos, double zpos);
        QDPoint &operator = (const QDPoint  &point_2);
        friend QTextStream & operator << (QTextStream & out, const QDPoint &p);
        double x()const;
        double y()const;
        double z()const;
        double& rx();
        double& ry();
        double& rz();
        void setX(double x);
        void setY(double y);
        void setZ(double z);
    private:
        double px;
        double py;
        double pz;
};

bool compareX(QDPoint p1, QDPointp2)
{
    if(abs(p1.x() - p2.x()) < CMP_EPS)
        return true;
    else
        return false;
};

bool compareY(QDPoint p1, QDPointp2)
{
    if(abs(p1.y() - p2.y()) < CMP_EPS)
        return true;
    else
        return false;
};

bool compareZ(QDPoint p1, QDPointp2)
{
    if(abs(p1.z() - p2.z()) < CMP_EPS)
        return true;
    else
        return false;
};
#endif // QDPOINT_H
