#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMenu>
#include "QDPoint.h"
#include "operators.h"
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void about();
    void exit();
private:
    Ui::MainWindow *ui;
    QMenu *menu;
    void create_menu();
};
#endif // MAINWINDOW_H
