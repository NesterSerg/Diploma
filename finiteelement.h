#ifndef FINITEELEMENT_H
#define FINITEELEMENT_H
#include <QVector>
#include "QDPoint.h"
class FiniteElement
{
    public:
        FiniteElement();
        FiniteElement(QVector <QDPoint>& vec);
        FiniteElement &operator = (FiniteElement &element_2);
        QDPoint &operator [](int i);
        friend QTextStream & operator << (QTextStream & out, FiniteElement &e);
        unsigned int getnumvert();// возвращает количество вершин
    private:
        QVector <QDPoint> vertexs;
        unsigned int numvertexs;
};
#endif // FINITEELEMENT_H
