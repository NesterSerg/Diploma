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
    loadPath();

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
    menu->addAction("&Выбрать папку", this, SLOT(selectDirectory()));// добавляем действие "Выбрать папку"
    ui->menuBar->addMenu(menu);
}

void MainWindow::about()//справка
{

}

void MainWindow::exit()//выход
{
    this->close();
}

void MainWindow::loadPath()
{
    QFile file("path.txt");
    QTextStream in(&file);
    if(file.open(QFile::ReadOnly| QFile::Text))
        directory = in.readAll();
    else
        QMessageBox::information(this,"Внимание","Укажите путь к папке с исходными файлами");
    file.close();
}

void MainWindow::savePath()
{
    QFile file("path.txt");
    QTextStream ou(&file);
    file.open(QFile::WriteOnly| QFile::Text);
    ou << directory;
    file.close();
}
void MainWindow::selectDirectory()
{
    directory = QFileDialog::getExistingDirectory(this, "Выберите папку с исходными файлами", "/home", QFileDialog::ShowDirsOnly  |QFileDialog::DontResolveSymlinks );
    savePath();
}

void MainWindow::on_pushButton_clicked()
{
    net.createNet(directory);
    ui->widget->setNet(&net);
    ui->widget->setFocus();
    ui->widget->update();
}

void MainWindow::on_WcheckBox_clicked()
{
    if(ui->widget->color)
        ui->widget->color = false;
    else
        ui->widget->color = true;
    ui->widget->setFocus();
    ui->widget->update();
}
