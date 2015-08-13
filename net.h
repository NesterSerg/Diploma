#ifndef NET_H
#define NET_H
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QString>
#include "QDPoint.h"
#include "operators.h"
#include "index3.h"


class Net
{
public:
    Net();
    Net(QString& filename);
    ~Net();
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
     QVector<QVector<double> > CLSections;// массив криволинейных участков
// Сетка
     int Nx, Ny, Nz;// количество точек по каждой из координат
     QVector< QVector< QVector<Index3> > > IndexOfRefPoints;// массив индексов опорных точек в дробленной сетке

     QVector< QVector< QVector<QDPoint> > > FNet;// массив дробленной сетки (Fragmented net)
     int getGlobalId(int i, int j, int k);// возвращает глобальный индекс узла
     void allocation();// выделение памяти
     void curvilinearAccounting();// учёт криволинейнх областей
     void createNet();
public:
     QDPoint getFNet(int i, int j, int k);// доступ массиву FNet
     int sizeX();
     int sizeY();
     int sizeZ();




// Другие методы
     void loadInfoFromFile(QString& filename);
};

#endif // NET_H









