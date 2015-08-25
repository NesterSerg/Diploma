#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_1_Compatibility>


#include <QMouseEvent>
#include <QKeyEvent>
#include "Net.h"
class MyGLWidget :  public QOpenGLWidget, protected QOpenGLFunctions
{
public:

    Net *net;
    MyGLWidget(QWidget *parent);
    int flag = 0;
    void drawNet();
    void setNet(Net *n);
protected :
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void wheelEvent(QWheelEvent* pe);
    void keyPressEvent(QKeyEvent* pe);
private:
    QOpenGLFunctions_4_1_Compatibility *f;
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat xTra;
    GLfloat zTra;
    GLfloat nSca;

    QPoint ptrMousePosition;

    void scale_plus();
    void scale_minus();
    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();
    void translate_down();
    void translate_up();
    void defaultScene();

};

#endif // MYGLWIDGET_H
