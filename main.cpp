
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    MainWindow w;    
    w.show();

    return a.exec();
}
