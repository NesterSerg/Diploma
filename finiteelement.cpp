#include "finiteelement.h"

FiniteElement::FiniteElement()
{
    numvertexs = 8;
    vertexs.resize(numvertexs);
}

FiniteElement::FiniteElement(QVector<Index3> &vec)
{
    numvertexs = 8;
    vertexs.resize(numvertexs);
    for(unsigned int i = 0; i < numvertexs; i++)
        vertexs[i] = vec[i];
}


Index3 &FiniteElement::operator [](int i)
{
    return vertexs[i];
}

int FiniteElement::W() const
{
    return w;
}

int &FiniteElement::rw()
{
    return w;
}

unsigned int FiniteElement::getnumvert()
{
    return numvertexs;
}

QTextStream& operator <<(QTextStream &out, FiniteElement &e)
{
    unsigned int tmp = e.getnumvert();
    for(unsigned int i = 0; i < tmp; i++)
       out << e[i].i << " "<< e[i].j << " "<< e[i].k << " ";
    out << e.W() << "\n";
    return out;
}
