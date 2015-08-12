#include "net.h"

Net::Net()
{

}

void Net::allocation()
{
// Выделение памяти под раздробленную сетку
    for(int i = 0; i < XSegments.size(); i++)// по оси X
        Nx += XSegments[i];
    Nx++;
    FNet.resize(Nx);

    for(int i = 0; i < YSegments.size(); i++)// по оси Y
        Ny += YSegments[i];
    Ny++;
    for(int i = 0; i < FNet.size(); i++)
        FNet[i].resize(Ny);

    for(int i = 0; i < ZSegments.size(); i++)// по оси Z
        Nz += ZSegments[i];
    Nz++;
    for(int i = 0; i < FNet.size(); i++)
        for(int j = 0; j < FNet[i].size(); j++)
            FNet[i][j].resize(Nz);

// Выделение памяти под массив индексов опорных точек
        IndexOfRefPoints.resize(Nwx);
        for(int i = 0; i < Nwx; i++)
        {
            IndexOfRefPoints[i].resize(Nwy);
            for(int j = 0; j < Nwy; j++)
                IndexOfRefPoints[i][j].resize(Nwz);
        }

// Высчитываем индексы опорных узлов в р. сетке
    for(int k = 0; k < Nwz; k++)
    for(int j = 0; j < Nwy; j++)
    for(int i = 0; i < Nwx; i++)
    {
        IndexOfRefPoints[i][j][k].i = 0;
        for(int t = 0; t < i; t++)
            IndexOfRefPoints[i][j][k].i += XSegments[t];

        IndexOfRefPoints[i][j][k].j = 0;
        for(int t = 0; t < j; t++)
            IndexOfRefPoints[i][j][k].j += YSegments[t];

        IndexOfRefPoints[i][j][k].k = 0;
        for(int t = 0; t < k; t++)
            IndexOfRefPoints[i][j][k].k += ZSegments[t];
    }
}

void Net::curvilinearAccounting()
{
    for(int m = 0; m < NCL; m++)// обрабатываем все криволин. участки
    {
        switch(int(CLSections[m][0]))
        {
        case 1:// если искривление по горизонтали (по оси X)
            break;
        case -1:// если искривление по вертикали (по оси Y)
            break;
        case -10:// если искривление по оси Z
            break;
        default:
            qDebug() << "Ошибка: Некорректный номер признака искривления! (Должен быть 1, -1, -10)";
            break;
        }

    }
}

void Net::createNet()
{
    allocation();// выделяем память под элементы, подсчитываем индексы опорных точек в сетке
}

int Net::getGlobalId(int i, int j, int k)
{
    return i + j * Nx + k * Nx * Ny;
}
//------
void Net::loadInfoFromFile(QString& filename)
{
    QFile file(filename);
    QTextStream in(&file);
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        QString bufString;
        double bufDouble;

    //Считывание числа опорных точек по координатам
        in >> bufString;// "Количество_опорных_точек_по_координатам"
        in >> Nwx >> Nwy >> Nwz;
        NAll = Nwx * Nwy * Nwz;

    //Выделение памяти под опорные точки
        RefPoints.resize(Nwx);
        for(int i = 0; i < Nwx; i++)
        {
            RefPoints[i].resize(Nwy);
            for(int j = 0; j < Nwy; j++)
                RefPoints[i][j].resize(Nwz);
        }

    //Считывание опорных точек
        in >> bufString;// "Опорные_точки"
        for(int k = 0; k < Nwz; k++)
        for(int j = 0; j < Nwy; j++)
        for(int i = 0; i < Nwx; i++)
        {
            in >> bufDouble; RefPoints[i][j][k].setX(bufDouble);
            in >> bufDouble; RefPoints[i][j][k].setY(bufDouble);
            in >> bufDouble; RefPoints[i][j][k].setZ(bufDouble);

        }
    //Считывание информации о разбиении сетки
        in >> bufString;// "Информация_о_разбиении"
        XSegments.resize(Nwx - 1); XCoD.resize(Nwx - 1);
        for(int i = 0; i < Nwx - 1; i++)
        {
            in >> XSegments[i];
            in >> XCoD[i];
        }
        YSegments.resize(Nwy - 1); YCoD.resize(Nwy - 1);
        for(int i = 0; i < Nwy - 1; i++)
        {
            in >> YSegments[i];
            in >> YCoD[i];
        }
        ZSegments.resize(Nwz - 1); ZCoD.resize(Nwz - 1);
        for(int i = 0; i < Nwz - 1; i++)
        {
            in >> ZSegments[i];
            in >> ZCoD[i];
        }
    //Считывание информации о подобластях
        in >> bufString;// "Число_подобластей"
        in >> Nw;
        in >> bufString;// "Номер_и_границы_подобластей"
        Subareas.resize(Nw);
        for(int i = 0; i < Nw; i++)
        {
            Subareas[i].resize(7);
            for(int j = 0; j < 7; j++)
                in >> Subareas[i][j];
        }

    //Считывание информации о криволинейных участках
        in >> bufString;// "Информация_о_криволинейных_участках"
        in >> NCL;
        CLSections.resize(NCL);
        for(int i = 0; i < NCL; i++)
        {
            CLSections[i].resize(7);
            for(int j = 0; j < 7; j++)
                in >> CLSections[i][j];
        }

}



