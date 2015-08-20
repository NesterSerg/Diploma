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

bool Index3::operator ==(const Index3 &ind2) const
{
    return this->i == ind2.i && this->j == ind2.j && this->k == ind2.k;
}



