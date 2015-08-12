#ifndef QDPOINT_H
#define QDPOINT_H
#include <QTextStream>
class QDPoint
{
    public:
        QDPoint();
        QDPoint(double xpos, double ypos, double zpos);
        QDPoint &operator = (QDPoint &point_2);
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

#endif // QDPOINT_H
