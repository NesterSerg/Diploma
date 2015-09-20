#ifndef LIB
#define LIB

#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QTextStream>

#include <math.h>
#include <iostream>
#include <fstream>
#include <float.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include "QDPoint.h"
#include "index3.h"

//ребро
class Edge
{
public:
    QVector<int> Nodes;
    int GlobalId;
};


#endif // LIB

