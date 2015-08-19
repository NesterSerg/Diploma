#ifndef NET_H
#define NET_H
//#include <QVector>
//#include <QTextStream>
//#include <QFile>
//#include <QString>
//#include "index3.h"

#include "lib.h"

#include "operators.h"



class Net
{
public:
    Net();
    Net(QString& filename);
    ~Net();

    void createNet();
private:
// Опорные точки
     int Nwx, Nwy, Nwz;// количество опорных точек по каждой координате
     int NAll;// общее число опорных точек
     QVector< QVector< QVector<QDPoint> > > RefPoints;// опорные точки(Reference points)
// Информация о разбиении сетки
     QVector<int> XSegments, YSegments, ZSegments;// массивы для хранения числа отрезков между опорными точками
     QVector<double> XCoD, YCoD, ZCoD;// массивы для хранения коэффициентов разрядки (CoD ~ Coefficient of discharge)
// Подобласти
     int Nw;// количество подобластей
     QVector< QVector<int> > Subareas;// массив подобластей
// Криволинейные участки
     int NCL;// количество криволинейных участков(curvilinear)
     int CL_X, CL_Y, CL_Z;// кол-во кривол. участвок по каждой из осей
     QVector< QVector<Index3> > OnX, OnY, OnZ;// вектора, в которых хранятся глобальные индексы опорных узлов
                                              // на криволинейных участках, между ними не обрабатываем
     QVector<QVector<double> > CLSections;// массив криволинейных участков
     void calcPointOnCL(QDPoint p1, QDPoint p2, QDPoint center, int Np, double CoD, Index3 index1, Index3 index2, int mode);// подсчет координат
                                       //точек на кривол. участке по 2 крайним точкам, коэф. разрядки и числу отрезков
     void calcPointOnSegments();
     bool isRPointsOnCL(Index3 i1, Index3 i2, int mode);// проверка индексов опорных точек, явл-я ли точки кривол. или нет
                                                        // mode - по какой оси смотрим, 1 - Ox, -1 - Oy, -10 - Oz
// Сетка
     int Nx, Ny, Nz;// количество точек по каждой из координат
     QVector< QVector< QVector<Index3> > > IndexOfRefPoints;// массив индексов опорных точек в дробленной сетке
     QVector< QVector< QVector<QDPoint> > > FNet;// массив дробленной сетки (Fragmented net)
     void allocation();// выделение памяти
     int getGlobalId(int i, int j, int k);// возвращает глобальный индекс узла

     void curvilinearAccounting();// учёт криволинейнх областей

public:
     QDPoint getFNet(int i, int j, int k);// доступ массиву FNet
     int sizeX();
     int sizeY();
     int sizeZ();




// Другие методы
     void loadInfoFromFile(QString& filename);
};

#endif // NET_H









