#ifndef QDPOINT_H
#define QDPOINT_H
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
        bool compareX(const QDPoint &p2);
        bool compareY(const QDPoint &p2);
        bool compareZ(const QDPoint &p2);
    private:
        double px;
        double py;
        double pz;
        const double  CMP_EPS = 1e-10;
};


#endif // QDPOINT_H
