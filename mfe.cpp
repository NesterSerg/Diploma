#include "mfe.h"

MFE::MFE(QObject *parent) : QObject(parent)
{

}

void MFE::createFE()
{
    //Nfe =; // количество конечных элементов
    FE.resize(Nfe);
    int sizeZ = net.sizeZ();
    int sizeY = net.sizeY();
    int sizeX = net.sizeX();
    FiniteElement F;
    Index3 INDEX;
    for(int k = 0; k < sizeZ - 1; k++)
    for(int j = 0; j < sizeY - 1; j++)
    for(int i = 0; i < sizeX - 1; i++)
    {
        // наверное как-то надо переделать в цикл
        INDEX.setIndex(i,j,k);
        F[0] = INDEX;
        INDEX.setIndex(i + 1,j,k);
        F[1] = INDEX;
        INDEX.setIndex(i,j + 1,k);
        F[2] = INDEX;
        INDEX.setIndex(i + 1,j + 1,k);
        F[3] = INDEX;

        INDEX.setIndex(i,j,k + 1);
        F[4] = INDEX;
        INDEX.setIndex(i + 1,j,k + 1);
        F[5] = INDEX;
        INDEX.setIndex(i,j + 1,k + 1);
        F[6] = INDEX;
        INDEX.setIndex(i + 1,j + 1,k + 1);
        F[7] = INDEX;

        //F.rw() =; // номер области
        FE.push_back(F);


    }
}

void MFE::printFE(QString &filename)
{
    QFile file(filename);
    QTextStream ou(&file);
    if(file.open(QFile::WriteOnly | QFile::Text))
        for(int i = 0; i < Nfe; i++)
            ou << FE[i] <<"\n";
    file.close();

}


