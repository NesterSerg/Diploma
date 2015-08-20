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
    bool operator == (const Index3 &ind2) const;

};

#endif // INDEX3_H
