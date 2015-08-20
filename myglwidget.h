#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QOpenGLWidget>
#include<QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_1_Compatibility>

#include <QUuid>
class MyGLWidget :  public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    MyGLWidget(QWidget *parent);
protected :
    void initializeGL() ;
    void resizeGL(int w, int h);
    void paintGL();
private:
    QOpenGLFunctions_4_1_Compatibility *f;

};

#endif // MYGLWIDGET_H
