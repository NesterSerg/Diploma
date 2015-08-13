#ifndef INDEX3_H
#define INDEX3_H


class Index3
{
public:
    Index3();
    int i;
    int j;
    int k;
    void setIndex(int i, int j, int k);
    Index3 &operator = (const Index3 &index_2);
};

#endif // INDEX3_H
