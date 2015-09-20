#ifndef FINITEELEMENT_H
#define FINITEELEMENT_H
#include "lib.h"

class FiniteElement
{
    public:
        FiniteElement();
        FiniteElement(QVector <int>& node, QVector <int>& edge);

        int &operator [](int i);

        friend QTextStream & operator << (QTextStream & out, FiniteElement &e);
        int W()const;
        int& rw();
        unsigned int getCountOfNodes();// возвращает количество вершин
        unsigned int getCountOfEdges();// возвращает количество вершин
        int getNodeId(int i);//возвращает элемент NodesId
        int getEdgeId(int i);//возвращает элемент EdgeId
        void setNodeId(int i, int Id);//задает элемент NodesId
        void setEdgeId(int i, int Id);//задает элемент EdgeId
        int getW();
        void setW(int numOfW);
        QVector<int> NodesId;// номера узлов
        QVector<int> EdgesId;// ребра КЭ
        int w;// номер области
        unsigned int countOfNodes;
        unsigned int countOfEdges;
};

#endif // FINITEELEMENT_H
