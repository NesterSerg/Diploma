#include "finiteelement.h"

FiniteElement::FiniteElement()
{
    countOfNodes = 8;
    NodesId.resize(countOfNodes);

    countOfEdges = 12;
    EdgesId.resize(countOfEdges);
}

FiniteElement::FiniteElement(QVector<int> &node, QVector <int>&edge)
{
    countOfNodes = 8;
    NodesId.resize(countOfNodes);
    if(node.size() == NodesId.size())
    for(unsigned int i = 0; i < countOfNodes; i++)
        NodesId[i] = node[i];

    countOfEdges = 8;
    EdgesId.resize(countOfEdges);
    if(edge.size() == EdgesId.size())
    for(unsigned int i = 0; i < countOfEdges; i++)
        EdgesId[i] = edge[i];
}


int &FiniteElement::operator [](int i)
{
    return NodesId[i];
}

int FiniteElement::W() const
{
    return w;
}

int &FiniteElement::rw()
{
    return w;
}

unsigned int FiniteElement::getCountOfNodes()
{
    return countOfNodes;
}

unsigned int FiniteElement::getCountOfEdges()
{
    return countOfEdges;
}

int FiniteElement::getNodeId(int i)
{
    return NodesId[i];
}

int FiniteElement::getEdgeId(int i)
{
    return EdgesId[i];
}

void FiniteElement::setNodeId(int i, int Id)
{
    NodesId[i] = Id;
}

void FiniteElement::setEdgeId(int i, int Id)
{
    EdgesId[i] = Id;
}

int FiniteElement::getW()
{
    return w;
}

void FiniteElement::setW(int numOfW)
{
    w = numOfW;
}


QTextStream& operator <<(QTextStream &out, FiniteElement &e)
{
    unsigned int tmp = e.getCountOfNodes();
    //for(unsigned int i = 0; i < tmp; i++)
    //   out << e[i].i << " "<< e[i].j << " "<< e[i].k << " ";
    //out << e.W() << "\n";
    return out;
}
