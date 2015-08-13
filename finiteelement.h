#ifndef FINITEELEMENT_H
#define FINITEELEMENT_H
#include <QVector>
#include <QTextStream>
#include "index3.h"
class FiniteElement
{
    public:
        FiniteElement();
        FiniteElement(QVector <Index3>& vec);
        FiniteElement &operator = (const FiniteElement &element_2);

        Index3 &operator [](int i);
        const Index3 & getconstref(int i)const;
        friend QTextStream & operator << (QTextStream & out, FiniteElement &e);
        int W()const;
        int& rw();
        unsigned int getnumvert();// возвращает количество вершин
    private:
        QVector <Index3> vertexs;// номера вершин
        int w;// номер области
        unsigned int numvertexs;
};
#endif // FINITEELEMENT_H
