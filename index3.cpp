#include "index3.h"

Index3::Index3()
{

}

void Index3::setIndex(int i, int j, int k)
{
    this->i = i;
    this->j = j;
    this->k = k;

}

Index3 &Index3::operator =(const Index3 &index_2)
{
    i = index_2.i;
    j = index_2.j;
    k = index_2.k;
    return *this;
}

