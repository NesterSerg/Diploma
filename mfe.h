#ifndef MFE_H
#define MFE_H
#include <QObject>
#include "net.h"
#include "finiteelement.h"

class MFE : public QObject
{
    Q_OBJECT
    public:
        explicit MFE(QObject *parent = 0);

    signals:

    public slots:

    private:
    Net net;

// КОНЕЧНЫЕ ЭЛЕМЕНТЫ
    int Nfe;// количество конечных элементов
    QVector <FiniteElement> FE;// спиок конечных элементов
    void createFE();// создание списка конечных элементов
    void printFE(QString& filename);

};
#endif // MFE_H
