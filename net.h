#ifndef NET_H
#define NET_H


#include "lib.h"
#include "operators.h"



class Net
{
public:
    Net();
    Net(QString& dir);
    ~Net();

    void clearNet();

    void createNet(QString& dir);
    void createFile();


private:
// Опорные точки
    int Nwx, Nwy, Nwz;// количество опорных точек по каждой координате
    QVector< QVector< QVector<QDPoint> > > RefPoints;// опорные точки(Reference points)
    int NwAll;// общее число опорных точек

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
     int Nx, Ny, Nz, NAll;// количество точек по каждой из координат, общее число точек
     QVector< QVector< QVector<Index3> > > IndexOfRefPoints;// массив индексов опорных точек в дробленной сетке
     QVector< QVector< QVector<QDPoint> > > FNet;// массив дробленной сетки (Fragmented net)
     void allocation();// выделение памяти

     void curvilinearAccounting();// учёт криволинейнх областей
//Данные, необходимые при работе с КЭ
     int NFE;
     int NEdges;//Общее число ребер

     QVector<QDPoint> Nodes;//Массив узлов     
     QVector<Edge> Edges;//Массив рёбер
     QVector<bool> FictNodes;// хранит информацию о том, является ля узел фиктивным (0 - фиктивный, 1 - действительный)
     QVector<bool> FictEdges;// аналогично предыдущему, только для ребер
     int NonFictNodes;//число нефиктивных узлов
     int NonFictEdges;//число нефиктивных рёбер
     QVector<int> newNodeNumeration;//новая нумерация узов(без фиктивных)
     QVector<int> newEdgeNumeration;//новая нумерация ребер(без фиктивных)

     void fillNodesInfo();
     void fillEdgesInfo();

     bool isNodeFict(int i, int j, int k);
     bool isNodeFict(Index3 index);



     // Другие методы

     void loadInfoFromFile(QString& filename);

public:
     QVector<QDPoint> bufNodes;//буферный вектор
     QVector<Edge> bufEdges;//буферный вектор
     QDPoint getFNet(int i, int j, int k);// доступ к массиву FNet
     QDPoint getFNet(Index3 index);//аналогично
     QDPoint getRefPoint(int i, int j, int k);// доступ к массиву RefPoints
     QDPoint getCentreMass();// возвращает центр сетки
     Index3 getIndexOfRefPoint(int i, int j, int k);// возврат индекса в глоб. сетке опорного узла

     QDPoint getNode(int i);//возвращает элемент из Nodes
     Edge getEdge(int i);//возвращает элемент из Edges
     bool isNodeFict(int GlobalId);//возвращает элемент из FictNodes
     bool isEdgeFict(int i);//возвращает элемент из FictEdges

     int getNodeGlobalId(int i, int j, int k);// возвращает глобальный индекс узла
     int getNodeGlobalId(Index3 index);// возвращает глобальный индекс узла
     //возвращает глобальный номер ребра, образованного узлом nodeId
     //и смежным с ним. mode = 1, -1, -10(x, y, z оси соответственно),
     //dir = 1, -1(следующий узел берется mode.координата+1)
     int getEdgeGlobalId(Index3 index, int mode, int dir);
     int getEdgeGlobalId(int i, int j, int k, int mode, int dir);

     int getNewNodeNumeration(int i);
     int getNewEdgeNumeration(int i);

     void swapNodes();
     void swapEdges();

     int sizeX();
     int sizeY();
     int sizeZ();

     int sizeW();
     int sizeXw();
     int sizeYw();
     int sizeZw();
     int getSubareas(int i, int j);

     int getNFE();
     int getNonFictNodes();
     int getNonFictEdges();
};

#endif // NET_H









