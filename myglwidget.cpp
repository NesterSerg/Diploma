#include "MyGLWidget.h"


MyGLWidget::MyGLWidget(QWidget *parent) :  QGLWidget(parent)
{
    xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1; xTra = 0;
    flag = 0;
    color = false;
    cof = 0.3;
}

void MyGLWidget::drawNet()
{

    double pi = 3.141592, _x, _y, _z;


    glLineWidth(2);
    double xCentre = 7, yCentre = 4, zCentre = 0, radius = 2;
    // Прорисовка окружности непосредственно.
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
        for (int angle = 0; angle <= 360; angle += 10)
        {
            // Координаты x, y повёрнутые на заданный угол относительно начала координат.
            double x = radius * cos(angle * pi / 180);
            double y = radius * sin(angle * pi / 180);
            // Смещаем окрущность к её центру [xCentre; yCentre].
            glVertex3d(cof * (x + xCentre - center_scene.x()), cof * (y + yCentre - center_scene.y()), cof * (zCentre - center_scene.z()));
        }
    glEnd();


    xCentre = 0; yCentre = 2; zCentre = 7.5; radius = 4.0311288;
    glBegin(GL_LINE_LOOP);
        for (int angle = 0; angle <= 360; angle += 10)
        {
            // Координаты x, y повёрнутые на заданный угол относительно начала координат.
            double y = radius * cos(angle * pi / 180);
            double z = radius * sin(angle * pi / 180);
            // Смещаем окрущность к её центру [xCentre; yCentre].
            glVertex3d(cof * (xCentre - center_scene.x()), cof * (y + yCentre - center_scene.y()), cof * (z+zCentre - center_scene.z()));
        }
    glEnd();


    //рисуем по подобластям
/*
    glLineWidth(1);
    glColor3f(0, 0, 0);
    for(int w = 0; w < net->sizeW(); w++)
    {
        int x1, x2, y1, y2, z1, z2;
        x1 = net->getIndexOfRefPoint(net->getSubareas(w, 1), net->getSubareas(w, 3), net->getSubareas(w, 5)).i;
        x2 = net->getIndexOfRefPoint(net->getSubareas(w, 2), net->getSubareas(w, 3), net->getSubareas(w, 5)).i;
        y1 = net->getIndexOfRefPoint(net->getSubareas(w, 1), net->getSubareas(w, 3), net->getSubareas(w, 5)).j;
        y2 = net->getIndexOfRefPoint(net->getSubareas(w, 2), net->getSubareas(w, 4), net->getSubareas(w, 5)).j;
        z1 = net->getIndexOfRefPoint(net->getSubareas(w, 1), net->getSubareas(w, 3), net->getSubareas(w, 5)).k;
        z2 = net->getIndexOfRefPoint(net->getSubareas(w, 2), net->getSubareas(w, 3), net->getSubareas(w, 6)).k;

        for(int k = z1; k <= z2; k++)
        for(int j = y1; j <= y2; j++)
        for(int i = x1; i < x2; i++)
        {
            glBegin(GL_LINES);
                glVertex3f(cof*net->getFNet(i, j, k).x() - cof*center_scene.x(), cof*net->getFNet(i, j, k).y() - cof*center_scene.y(), cof*net->getFNet(i, j, k).z() - cof*center_scene.z());
                glVertex3f(cof*net->getFNet(i+1, j, k).x() - cof*center_scene.x(), cof*net->getFNet(i+1, j, k).y() - cof*center_scene.y(), cof*net->getFNet(i+1, j, k).z() - cof*center_scene.z());
            glEnd();
        }

        for(int k = z1; k <= z2; k++)
        for(int i = x1; i <= x2; i++)
        for(int j = y1; j < y2; j++)
        {
            glBegin(GL_LINES);
                glVertex3f(cof*net->getFNet(i, j, k).x() - cof*center_scene.x(), cof*net->getFNet(i, j, k).y() - cof*center_scene.y(), cof*net->getFNet(i, j, k).z() - cof*center_scene.z());
                glVertex3f(cof*net->getFNet(i, j+1, k).x() - cof*center_scene.x(), cof*net->getFNet(i, j+1, k).y() - cof*center_scene.y(), cof*net->getFNet(i, j+1, k).z() - cof*center_scene.z());
            glEnd();
        }

        for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
        for(int k = z1; k < z2; k++)
        {
            glBegin(GL_LINES);
                glVertex3f(cof*net->getFNet(i, j, k).x() - cof*center_scene.x(), cof*net->getFNet(i, j, k).y() - cof*center_scene.y(), cof*net->getFNet(i, j, k).z() - cof*center_scene.z());
                glVertex3f(cof*net->getFNet(i, j, k+1).x() - cof*center_scene.x(), cof*net->getFNet(i, j, k+1).y() - cof*center_scene.y(), cof*net->getFNet(i, j, k+1).z() - cof*center_scene.z());
            glEnd();
        }
    }
*/

    //рисуем по КЭ
    FiniteElement FE;
    glColor3f(0, 0, 0);
    glLineWidth(1);
    for(int i = 0; i < mfe.FE.size(); i++)
    {
        FE = mfe.FE[i];

        for(int j = 0; j < 12; j++)
        {
            glBegin(GL_LINES);
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[j]].Nodes[0]].x() - center_scene.x() ) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[j]].Nodes[0]].y() - center_scene.y() ) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[j]].Nodes[0]].z() - center_scene.z() ) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[j]].Nodes[1]].x() - center_scene.x() ) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[j]].Nodes[1]].y() - center_scene.y() ) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[j]].Nodes[1]].z() - center_scene.z() ) * cof );
            glEnd();
        }
    }
}

void MyGLWidget::drawAxis()
{

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_COLOR_MATERIAL);

    glLineWidth(2);
    //Ободок камеры
    glPushMatrix();
    glLoadIdentity();
    glColor3ub(176, 196, 222);
    glBegin(GL_QUADS);
        glVertex3f(2.6, 1.6, 0);
        glVertex3f(2.6, 2.8, 0);
        glVertex3f(3.8, 2.8, 0);
        glVertex3f(3.8, 1.6, 0);
    glEnd();
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(2.6, 1.6, 2.9);
        glVertex3f(2.6, 2.8, 2.9);
        glVertex3f(3.8, 2.8, 2.9);
        glVertex3f(3.8, 1.6, 2.9);
    glEnd();
    glPopMatrix();
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);//glVertex3f(2.5, 0, 2.5);
        glVertex3f(0.4, 0, 0);//glVertex3f(2.7, 0, 2.5);
    glEnd();

    glColor3f(0, 0.5, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);//glVertex3f(2.5, 0, 2.5);
        glVertex3f(0, 0.4, 0);//glVertex3f(2.5, 0.2, 2.5);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);//glVertex3f(2.5, 0, 2.5);
        glVertex3f(0, 0, 0.4);//glVertex3f(2.5, 0, 2.7);
    glEnd();

   //if(light)
   //{
   //    glEnable(GL_LIGHTING);
   //    glEnable(GL_LIGHT0);
   //    glEnable(GL_COLOR_MATERIAL);
   //}

    glLineWidth(1);
}

void MyGLWidget::drawBrightW()
{
    /*
    for(int w = 0; w < net->sizeW(); w++)
    {
        int x1, x2, y1, y2, z1, z2;
        x1 = net->getIndexOfRefPoint(net->getSubareas(w, 1), net->getSubareas(w, 3), net->getSubareas(w, 5)).i;
        x2 = net->getIndexOfRefPoint(net->getSubareas(w, 2), net->getSubareas(w, 3), net->getSubareas(w, 5)).i;
        y1 = net->getIndexOfRefPoint(net->getSubareas(w, 1), net->getSubareas(w, 3), net->getSubareas(w, 5)).j;
        y2 = net->getIndexOfRefPoint(net->getSubareas(w, 2), net->getSubareas(w, 4), net->getSubareas(w, 5)).j;
        z1 = net->getIndexOfRefPoint(net->getSubareas(w, 1), net->getSubareas(w, 3), net->getSubareas(w, 5)).k;
        z2 = net->getIndexOfRefPoint(net->getSubareas(w, 2), net->getSubareas(w, 3), net->getSubareas(w, 6)).k;

        glColor3f(net->colorsW[w][0], net->colorsW[w][1], net->colorsW[w][2]);

        for(int k = z1; k < z2; k++)
        for(int j = y1; j < y2; j++)
        for(int i = x1; i < x2; i++)
        {
            glBegin(GL_QUADS);
                glVertex3f(cof*net->getFNet(i, j, k).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j, k).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i, j, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i+1, j, k).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j, k).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i+1, j, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i+1, j+1, k).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j+1, k).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i+1, j+1, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i, j+1, k).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j+1, k).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i, j+1, k).z()-cof*center_scene.z()+0.005);
            glEnd();

            glBegin(GL_QUADS);
                glVertex3f(cof*net->getFNet(i, j, k+1).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j, k+1).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i, j, k+1).z()-cof*center_scene.z()-0.005);
                glVertex3f(cof*net->getFNet(i+1, j, k+1).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j, k+1).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i+1, j, k+1).z()-cof*center_scene.z()-0.005);
                glVertex3f(cof*net->getFNet(i+1, j+1, k+1).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j+1, k+1).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i+1, j+1, k+1).z()-cof*center_scene.z()-0.005);
                glVertex3f(cof*net->getFNet(i, j+1, k+1).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j+1, k+1).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i, j+1, k+1).z()-cof*center_scene.z()-0.005);
            glEnd();

            glBegin(GL_QUADS);
                glVertex3f(cof*net->getFNet(i, j, k).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j, k).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i, j, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i+1, j, k).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j, k).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i+1, j, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i+1, j, k+1).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j, k+1).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i+1, j, k+1).z()-cof*center_scene.z()-0.005);
                glVertex3f(cof*net->getFNet(i, j, k+1).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j, k+1).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i, j, k+1).z()-cof*center_scene.z()-0.005);
            glEnd();

            glBegin(GL_QUADS);
                glVertex3f(cof*net->getFNet(i, j+1, k).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j+1, k).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i, j+1, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i+1, j+1, k).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j+1, k).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i+1, j+1, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i+1, j+1, k+1).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j+1, k+1).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i+1, j+1, k+1).z()-cof*center_scene.z()-0.005);
                glVertex3f(cof*net->getFNet(i, j+1, k+1).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j+1, k+1).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i, j+1, k+1).z()-cof*center_scene.z()-0.005);
            glEnd();

            glBegin(GL_QUADS);
                glVertex3f(cof*net->getFNet(i, j, k).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j, k).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i, j, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i, j+1, k).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j+1, k).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i, j+1, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i, j+1, k+1).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j+1, k+1).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i, j+1, k+1).z()-cof*center_scene.z()-0.005);
                glVertex3f(cof*net->getFNet(i, j, k+1).x()-cof*center_scene.x()+0.005, cof*net->getFNet(i, j, k+1).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i, j, k+1).z()-cof*center_scene.z()-0.005);
            glEnd();

            glBegin(GL_QUADS);
                glVertex3f(cof*net->getFNet(i+1, j, k).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j, k).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i+1, j, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i+1, j+1, k).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j+1, k).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i+1, j+1, k).z()-cof*center_scene.z()+0.005);
                glVertex3f(cof*net->getFNet(i+1, j+1, k+1).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j+1, k+1).y()-cof*center_scene.y()-0.005, cof*net->getFNet(i+1, j+1, k+1).z()-cof*center_scene.z()-0.005);
                glVertex3f(cof*net->getFNet(i+1, j, k+1).x()-cof*center_scene.x()-0.005, cof*net->getFNet(i+1, j, k+1).y()-cof*center_scene.y()+0.005, cof*net->getFNet(i+1, j, k+1).z()-cof*center_scene.z()-0.005);
            glEnd();
        }
    }
    */

    //рисуем по КЭ

    FiniteElement FE;

    glLineWidth(1);
    for(int i = 0; i < mfe.FE.size(); i++)
    {
        FE = mfe.FE[i];

        glColor3f(mfe.colorsW[FE.w][0], mfe.colorsW[FE.w][1], mfe.colorsW[FE.w][2]);
        for(int j = 0; j < 12; j++)
        {
            //нижняя грань
            glBegin(GL_QUADS);
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[0]].Nodes[0]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[0]].Nodes[0]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[0]].Nodes[0]].z() - center_scene.z() + 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[0]].Nodes[1]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[0]].Nodes[1]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[0]].Nodes[1]].z() - center_scene.z() + 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[1]].Nodes[1]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[1]].Nodes[1]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[1]].Nodes[1]].z() - center_scene.z() + 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[1]].Nodes[0]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[1]].Nodes[0]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[1]].Nodes[0]].z() - center_scene.z() + 0.005) * cof );

            glEnd();
            //верхняя
            glBegin(GL_QUADS);
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[4]].Nodes[0]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[4]].Nodes[0]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[4]].Nodes[0]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[4]].Nodes[1]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[4]].Nodes[1]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[4]].Nodes[1]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[5]].Nodes[1]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[5]].Nodes[1]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[5]].Nodes[1]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[5]].Nodes[0]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[5]].Nodes[0]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[5]].Nodes[0]].z() - center_scene.z() - 0.005) * cof );

            glEnd();
            //ближняя
            glBegin(GL_QUADS);
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[0]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[0]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[0]].z() - center_scene.z() + 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[1]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[1]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[1]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[9]].Nodes[1]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[9]].Nodes[1]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[9]].Nodes[1]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[9]].Nodes[0]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[9]].Nodes[0]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[9]].Nodes[0]].z() - center_scene.z() + 0.005) * cof );

            glEnd();
            //дальняя
            glBegin(GL_QUADS);
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[0]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[0]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[0]].z() - center_scene.z() + 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[1]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[1]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[1]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[1]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[1]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[1]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[0]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[0]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[0]].z() - center_scene.z() + 0.005) * cof );

            glEnd();
            //левая
            glBegin(GL_QUADS);
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[0]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[0]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[0]].z() - center_scene.z() + 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[1]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[1]].y() - center_scene.y() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[8]].Nodes[1]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[1]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[1]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[1]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[0]].x() - center_scene.x() + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[0]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[10]].Nodes[0]].z() - center_scene.z() + 0.005) * cof );

            glEnd();
            //правая
            glBegin(GL_QUADS);
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[3]].Nodes[0]].x() - center_scene.x()  - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[3]].Nodes[0]].y() - center_scene.y()  + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[3]].Nodes[0]].z() - center_scene.z()  + 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[3]].Nodes[1]].x() - center_scene.x()  - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[3]].Nodes[1]].y() - center_scene.y()  + 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[3]].Nodes[1]].z() - center_scene.z()  - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[1]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[1]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[1]].z() - center_scene.z() - 0.005) * cof );
                glVertex3d( (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[0]].x() - center_scene.x() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[0]].y() - center_scene.y() - 0.005) * cof,
                            (mfe.Nodes[mfe.Edges[FE.EdgesId[11]].Nodes[0]].z() - center_scene.z() + 0.005) * cof );

            glEnd();

        }
    }
}

void MyGLWidget::setFLAG()
{
    flag = 1;
    center_scene = mfe.centreMass;
}

void MyGLWidget::initializeGL()
{
    center_scene = mfe.centreMass;
    glClearColor(248./255, 244./255, 1, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);//GL_SMOOTH


    GLfloat light0_position[] = { 0.0, 2, 0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    GLfloat light0_diffuse[] = {1, 1, 1};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

    GLfloat ambience[] = {1.0f, 1.0f, 1.0f, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambience);
    GLfloat  light0_specular[] = { 1, 1, 1, 1} ;
    glLightfv ( GL_LIGHT0, GL_SPECULAR, light0_specular );
    glEnable(GL_NORMALIZE);


}

void MyGLWidget::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

    if (nWidth>=nHeight)
       glOrtho(-3.0/ratio, 3.0/ratio, -3.0, 3.0, -10.0, 10.0);
    else
       glOrtho(-3.0, 3.0, -3.0*ratio, 3.0*ratio, -10.0, 10.0);

    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void MyGLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(3.2, 2.2, 3);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    drawAxis();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(nSca, nSca, nSca);
    glTranslatef(cof*center_scene.x() + xTra,cof*center_scene.y() + zTra, cof*center_scene.z());
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    if(flag == 1)
    {
        if(color)
            drawBrightW();
        drawNet();

    }
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

