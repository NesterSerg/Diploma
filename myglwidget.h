#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include "lib.h"
#include "mfe.h"
class MyGLWidget :  public QGLWidget
{
public:

    MFE mfe;
    MyGLWidget(QWidget *parent);
    void drawNet();
    void drawAxis();
    void drawBrightW();
    void setFLAG();

    bool color;
    QDPoint center_scene;
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

    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat xTra;
    GLfloat zTra;
    GLfloat nSca;
    int flag;
    QPoint ptrMousePosition;

    double cof;



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

