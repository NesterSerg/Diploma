#include "myglwidget.h"


MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions();// типо функции опенджл, вот только не все
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1,0,0,0);


}

void MyGLWidget::resizeGL(int w, int h)
{

}

void MyGLWidget::paintGL()
{
    f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_1_Compatibility>();// тут типо отальные функции
    // херня какая-то, но видимо надо так делать теперь
    f->glColor3f(1.0, 1.0, 0.0);
    f->glBegin(GL_POLYGON);
        f->glVertex3f (0.25, 0.25, 0.0);
        f->glVertex3f (0.75, 0.25, 0.0);
        f->glVertex3f (0.75, 0.75, 0.0);
        f->glVertex3f (0.25, 0.75, 0.0);
    f->glEnd();



}


