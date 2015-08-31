/*#include "MyGLWidget.h"


MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1; xTra = 0;
}

void MyGLWidget::drawNet()
{
   /* double cof = 0.1;
    f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_1_Compatibility>();//
    for(int i = 0; i < net->sizeX(); i++)
    for(int j = 0; j < net->sizeY(); j++)
    for(int k = 0; k < net->sizeZ() - 1; k++)
    {
        f->glColor3f(0, 0, 0);
        f->glBegin(GL_LINES);
            f->glVertex3f(cof * net->getFNet(i, j, k).x(), cof * net->getFNet(i, j, k).y(),
                          cof * net->getFNet(i, j, k).z());
            f->glVertex3f(cof * net->getFNet(i, j, k).x(), cof * net->getFNet(i, j, k).y(),
                          cof * net->getFNet(i, j, k).z() + 1);
        f->glEnd();
    }

    for(int k = 0; k < net->sizeZ(); k++)
    for(int j = 0; j < net->sizeY(); j++)
    for(int i = 0; i < net->sizeX() - 1; i++)
    {
        f->glColor3f(0, 0, 0);
        f->glBegin(GL_LINES);
            f->glVertex3f(cof * net->getFNet(i, j, k).x(), cof * net->getFNet(i, j, k).y(),
                          cof * net->getFNet(i, j, k).z());
            f->glVertex3f(cof * net->getFNet(i, j, k).x() + 1, cof * net->getFNet(i, j, k).y(),
                          cof * net->getFNet(i, j, k).z());
        f->glEnd();
    }

    for(int i = 0; i < net->sizeX(); i++)
    for(int k = 0; k < net->sizeZ(); k++)
    for(int j = 0; j < net->sizeY() - 1; j++)
    {
        f->glColor3f(0, 0, 0);
        f->glBegin(GL_LINES);
            f->glVertex3f(cof * net->getFNet(i, j, k).x(), cof * net->getFNet(i, j, k).y(),
                          cof * net->getFNet(i, j, k).z());
            f->glVertex3f(cof * net->getFNet(i, j, k).x(), cof * net->getFNet(i, j, k).y() + 1,
                          cof * net->getFNet(i, j, k).z());
        f->glEnd();
    }
}

void MyGLWidget::setNet(Net *n)
{
    net = n;
}

void MyGLWidget::initializeGL()
{
    f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_1_Compatibility>();
    initializeOpenGLFunctions();// типо функции опенджл, вот только не все
    glClearColor(248./255, 244./255, 1, 0);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_SMOOTH);//GL_SMOOTH
    //
    //
    //GLfloat light0_position[] = { 0.0, 2, 0, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    //GLfloat light0_diffuse[] = {1, 1, 1};
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    //
    //GLfloat ambience[] = {1.0f, 1.0f, 1.0f, 0.0};
    //glLightfv(GL_LIGHT0, GL_AMBIENT,  ambience);
    //GLfloat  light0_specular[] = { 1, 1, 1, 1} ;
    //glLightfv ( GL_LIGHT0, GL_SPECULAR, light0_specular );
    //glEnable(GL_NORMALIZE);


}

void MyGLWidget::resizeGL(int nWidth, int nHeight)
{
    f->glMatrixMode(GL_PROJECTION);
    f->glLoadIdentity();

    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

    if (nWidth>=nHeight)
       f->glOrtho(-3.0/ratio, 3.0/ratio, -3.0, 3.0, -10.0, 10.0);
    else
       f->glOrtho(-3.0, 3.0, -3.0*ratio, 3.0*ratio, -10.0, 10.0);

    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void MyGLWidget::paintGL()
{
    drawNet();
}


//----------------------------------------------
void MyGLWidget::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent* pe)
{

}

void MyGLWidget::mouseMoveEvent(QMouseEvent* pe)
{
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();

   this->update();
}

void MyGLWidget::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

   this->update();
}

void MyGLWidget::keyPressEvent(QKeyEvent* pe)
{
   switch (pe->key())
   {
      case Qt::Key_Plus:
         scale_plus();
      break;

      case Qt::Key_Equal:
         scale_plus();
      break;

      case Qt::Key_Minus:
         scale_minus();
      break;

      case Qt::Key_Up:
         rotate_up();
      break;

      case Qt::Key_Down:
         rotate_down();
      break;

      case Qt::Key_Left:
        rotate_left();
      break;

      case Qt::Key_Right:
         rotate_right();
      break;

      case Qt::Key_Z:
         translate_down();
      break;

      case Qt::Key_X:
         translate_up();
      break;

      case Qt::Key_Space:
         defaultScene();
      break;

      case Qt::Key_Escape:
         this->close();
      break;
   }

   this->update();
}

void MyGLWidget::scale_plus()
{
   nSca = nSca*1.1;
}

void MyGLWidget::scale_minus()
{
   nSca = nSca/1.1;
}

void MyGLWidget::rotate_up()
{
   zTra += 0.05;
}

void MyGLWidget::rotate_down()
{
   zTra -= 0.05;
}

void MyGLWidget::rotate_left()
{
   xTra -= 0.05;
}

void MyGLWidget::rotate_right()
{
   xTra += 0.05;
}

void MyGLWidget::translate_down()
{
   zTra -= 0.05;
}

void MyGLWidget::translate_up()
{
   zTra += 0.05;
}

void MyGLWidget::defaultScene()
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}
*/
