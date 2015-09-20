#ifndef MFE_H
#define MFE_H
//#include <QObject>
#include "lib.h"
#include "net.h"
#include "finiteelement.h"
#include "matrixlu.h"
#include <set>

using namespace std;

class MFE : public QObject
{
    Q_OBJECT
    public:
        explicit MFE(QObject *parent = 0);

    signals:

    public slots:

    public:
    Net net;

    QDPoint centreMass;
    QVector< QVector<double> > colorsW;// цвета подобластей
// КОНЕЧНЫЕ ЭЛЕМЕНТЫ
    int nFE;// количество конечных элементов
    QVector<FiniteElement> FE;// спиок конечных элементов
    int nNodes;// число узлов
    QVector<QDPoint> Nodes;// список узлов
    int nEdges;//число ребер
    QVector<Edge> Edges;//список рёбер
    void createFE();// создание списка конечных элементов
    void printFE(QString& filename);
    QDPoint getNodeFromFE(int _nFE, int localId);
    Edge getEdgeFromFE(int _nFE, int localId);

// МАТРИЦА
    MatrixLU matrEdge;
    void buildPortraitEdge();


};
#endif // MFE_H
