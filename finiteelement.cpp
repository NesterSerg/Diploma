#include "finiteelement.h"

FiniteElement::FiniteElement()
{
    numvertexs = 4;
    vertexs.resize(numvertexs);
}

FiniteElement::FiniteElement(QVector<QDPoint> &vec)
{
    numvertexs = 4;
    vertexs.resize(numvertexs);
    for(unsigned int i = 0; i < numvertexs; i++)
        vertexs[i] = vec[i];
}

FiniteElement &FiniteElement::operator =(FiniteElement &element_2)
{
    for(unsigned int i = 0; i < numvertexs; i++)
        vertexs[i]  = element_2[i];
    return *this;
}

QDPoint &FiniteElement::operator [](int i)
{
    return vertexs[i];
}

unsigned int FiniteElement::getnumvert()
{
    return numvertexs;
}

QTextStream& operator <<(QTextStream &out, FiniteElement &e)
{
    unsigned int tmp = e.getnumvert();
    for(unsigned int i = 0; i < tmp; i++)
       out <<"vertex " << i << ": "<< e[i] << "\n";
    return out;
}

