#include "mfe.h"

MFE::MFE(QObject *parent) : QObject(parent)
{
}

void MFE::createFE()
{

    //генерируем цвета подобластей
    colorsW.resize(net.sizeW());
    for(int i = 0; i < net.sizeW(); i++)
    {
        colorsW[i].resize(3);
        for(int j = 0; j < 3; j++)
            colorsW[i][j] = (rand()%255)/255.;
    }

    nFE = net.getNFE(); // количество конечных элементов
    FE.resize(nFE);
    int sizeZ = net.sizeZ();
    int sizeY = net.sizeY();
    int sizeX = net.sizeX();
    int sizeW = net.sizeW();
    FiniteElement F;
    Index3 INDEX;
    int countF = 0;

    for(int w = 0; w < sizeW; w++)
    {
        int x1, x2, y1, y2, z1, z2;
        x1 = net.getIndexOfRefPoint(net.getSubareas(w, 1), net.getSubareas(w, 3), net.getSubareas(w, 5)).i;
        x2 = net.getIndexOfRefPoint(net.getSubareas(w, 2), net.getSubareas(w, 3), net.getSubareas(w, 5)).i;
        y1 = net.getIndexOfRefPoint(net.getSubareas(w, 1), net.getSubareas(w, 3), net.getSubareas(w, 5)).j;
        y2 = net.getIndexOfRefPoint(net.getSubareas(w, 2), net.getSubareas(w, 4), net.getSubareas(w, 5)).j;
        z1 = net.getIndexOfRefPoint(net.getSubareas(w, 1), net.getSubareas(w, 3), net.getSubareas(w, 5)).k;
        z2 = net.getIndexOfRefPoint(net.getSubareas(w, 2), net.getSubareas(w, 3), net.getSubareas(w, 6)).k;

        for(int k = z1; k < z2; k++)
        for(int j = y1; j < y2; j++)
        for(int i = x1; i < x2; i++)
        {
            //задаем глобальные номера узлов
            F.setNodeId(0, net.getNewNodeNumeration(net.getNodeGlobalId(i, j, k)) );
            F.setNodeId(1, net.getNewNodeNumeration(net.getNodeGlobalId(i+1, j, k)) );
            F.setNodeId(2, net.getNewNodeNumeration(net.getNodeGlobalId(i, j+1, k)) );
            F.setNodeId(3, net.getNewNodeNumeration(net.getNodeGlobalId(i+1, j+1, k)) );

            F.setNodeId(4, net.getNewNodeNumeration(net.getNodeGlobalId(i, j, k+1)) );
            F.setNodeId(5, net.getNewNodeNumeration(net.getNodeGlobalId(i+1, j, k+1)) );
            F.setNodeId(6, net.getNewNodeNumeration(net.getNodeGlobalId(i, j+1, k+1)) );
            F.setNodeId(7, net.getNewNodeNumeration(net.getNodeGlobalId(i+1, j+1, k+1) ));

            //задаем глобальные номера ребер
            F.setEdgeId(0, net.getNewEdgeNumeration(net.getEdgeGlobalId(i, j, k, -1, 1)) );
            F.setEdgeId(1, net.getNewEdgeNumeration(net.getEdgeGlobalId(i+1, j, k, -1, 1)) );
            F.setEdgeId(2, net.getNewEdgeNumeration(net.getEdgeGlobalId(i, j, k, 1, 1)) );
            F.setEdgeId(3, net.getNewEdgeNumeration(net.getEdgeGlobalId(i, j+1, k, 1, 1)) );

            F.setEdgeId(4, net.getNewEdgeNumeration(net.getEdgeGlobalId(i, j, k+1, -1, 1)) );
            F.setEdgeId(5, net.getNewEdgeNumeration(net.getEdgeGlobalId(i+1, j, k+1, -1, 1)) );
            F.setEdgeId(6, net.getNewEdgeNumeration(net.getEdgeGlobalId(i, j, k+1, 1, 1)) );
            F.setEdgeId(7, net.getNewEdgeNumeration(net.getEdgeGlobalId(i, j+1, k+1, 1, 1)) );

            F.setEdgeId(8, net.getNewEdgeNumeration(net.getEdgeGlobalId(i, j, k, -10, 1)) );
            F.setEdgeId(9, net.getNewEdgeNumeration(net.getEdgeGlobalId(i+1, j, k, -10, 1)) );
            F.setEdgeId(10, net.getNewEdgeNumeration(net.getEdgeGlobalId(i, j+1, k, -10, 1)) );
            F.setEdgeId(11, net.getNewEdgeNumeration(net.getEdgeGlobalId(i+1, j+1, k, -10, 1)) );

            //задаем номер подобласти
            F.setW(w);

            FE[countF] = F;
            countF++;
        }
    }

    Nodes.resize(net.getNonFictNodes());
    Nodes = net.bufNodes;
    nNodes = Nodes.size();

    Edges.resize(net.getNonFictEdges());
    Edges = net.bufEdges;
    nEdges = Edges.size();

    centreMass = net.getCentreMass();
    net.clearNet();
}

void MFE::printFE(QString &filename)
{
    QFile file(filename);
    QTextStream ou(&file);
    if(file.open(QFile::WriteOnly | QFile::Text))
        for(int i = 0; i < nFE; i++)
            ou << FE[i] <<"\n";
    file.close();

}

QDPoint MFE::getNodeFromFE(int _nFE, int localId)
{
    return Nodes[FE[_nFE].NodesId[localId]];
}

Edge MFE::getEdgeFromFE(int _nFE, int localId)
{
    return Edges[FE[_nFE].EdgesId[localId]];
}

void MFE::buildPortraitEdge()
{
    matrEdge.di.resize(nEdges);
    matrEdge.D.resize(nEdges);

    int	Edge_Index[12];// номера узлов коненого элемента √ЋќЅјЋ№Ќџ≈
    std::vector< std::set<int> >lisp;
    lisp.resize(nEdges);
    for(int i = 0; i < nFE; i++)
    {
        //qDebug() << "КЭ №" << i << "\n";
        Edge_Index[0] = FE[i].EdgesId[2];
        Edge_Index[1] = FE[i].EdgesId[0];
        Edge_Index[2] = FE[i].EdgesId[1];
        Edge_Index[3] = FE[i].EdgesId[3];
        Edge_Index[4] = FE[i].EdgesId[8];
        Edge_Index[5] = FE[i].EdgesId[9];
        Edge_Index[6] = FE[i].EdgesId[10];
        Edge_Index[7] = FE[i].EdgesId[11];
        Edge_Index[8] = FE[i].EdgesId[6];
        Edge_Index[9] = FE[i].EdgesId[4];
        Edge_Index[10] = FE[i].EdgesId[5];
        Edge_Index[11] = FE[i].EdgesId[7];

        for(int k = 1; k < 12; k++)
            for(int m = 0; m < k; m++)
                lisp[Edge_Index[k]].insert(Edge_Index[m]);
    }

    matrEdge.ig.resize(nEdges + 1);
    matrEdge.ig[0] = 0;
    for (int i = 1; i < nEdges + 1; i++)
        matrEdge.ig[i] = matrEdge.ig[i - 1] + lisp[i - 1].size();
    matrEdge.ggl.resize(matrEdge.ig[nEdges]);
    matrEdge.ggu.resize(matrEdge.ig[nEdges]);
    matrEdge.jg.resize(matrEdge.ig[nEdges]);
    int tmp = 0;
    for (int i = 1; i < nEdges; i++)
    {
        for (std::set<int>::iterator iter = lisp[i].begin(); iter != lisp[i].end(); iter++)
        {
            //qDebug() << "Edge: " << i << "\n";
            matrEdge.jg[tmp] = (*iter);
            tmp++;
        }
    }

}


