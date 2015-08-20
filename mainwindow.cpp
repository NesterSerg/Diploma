#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_menu();    
    ui->MainLayout->setStretchFactor(ui->OpenglLayout,9);
    ui->MainLayout->setStretchFactor(ui->MenuLayout,1);


}

MainWindow::~MainWindow()
{
    delete menu;
    delete ui;
}

void MainWindow::MainWindow::create_menu()
{
    menu = new QMenu("&Меню"); // создаём меню
    menu->addAction("&Справка", this, SLOT(about()), Qt::CTRL + Qt::Key_Q);// добавляем действие "Справка"
    menu->addAction("&Выход", this, SLOT(exit()), Qt::Key_Escape);// добавляем действие "Выход"
    ui->menuBar->addMenu(menu);
}

void MainWindow::about()//справка
{

}

void MainWindow::exit()//выход
{
    this->close();
}
