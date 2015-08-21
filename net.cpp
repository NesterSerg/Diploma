#include "net.h"
#include "geometry.h"

Net::Net()
{

}

Net::Net(QString &dir)
{

}

Net::~Net()
{

}
/*
Криволинейные участки
*/

void Net::calcPointOnCL(QDPoint p1, QDPoint p2, QDPoint center, int Np, double CoD, Index3 index1, Index3 index2, int mode)
{
/*
I. Вычисляем положение точек на ХОРДЕ
II. Находим угол между получившимися прямыми
III. Поворачиваем начальную точку на соотв. угол
*/

//I. Вычисляем положение точек на ХОРДЕ
  // Np - число отрезков на крив. участке
  // Np - 1 - число доп. точек между p1 и p2
    double lengthX, lengthY, lengthZ; // длины по соотв. координатам
    double hx, hy, hz;// шаги по соотв. координатам
    double _i = index1.i, _j = index1.j, _k = index1.k;

  // Вычисляем длины интервалов по соотв. координатам
    //lengthX = getLengthX(p1, p2);
    //lengthY = getLengthY(p1, p2);
    //lengthZ = getLengthZ(p1, p2);
    lengthX = p2.x() - p1.x();
    lengthY = p2.y() - p1.y();
    lengthZ = p2.z() - p1.z();
  // Вычисляем величину начального шага
    if(fabs(1-CoD) > 1e-10)
    {
        hx = lengthX * ((1-CoD)/(1-pow(CoD, Np)));
        hy = lengthY * ((1-CoD)/(1-pow(CoD, Np)));
        hz = lengthZ * ((1-CoD)/(1-pow(CoD, Np)));
    }
    else
    {
        hx = lengthX / Np;
        hy = lengthY / Np;
        hz = lengthZ / Np;
    }
  // Обрабатываем 1 доп. точку
    switch(mode)
    {
    case 1:
        FNet[_i + 1][_j][_k].setX(FNet[_i][_j][_k].x() + hx);
        FNet[_i + 1][_j][_k].setY(FNet[_i][_j][_k].y() + hy);
        FNet[_i + 1][_j][_k].setZ(FNet[_i][_j][_k].z() + hz);
        break;
    case -1:
        FNet[_i][_j + 1][_k].setX(FNet[_i][_j][_k].x() + hx);
        FNet[_i][_j + 1][_k].setY(FNet[_i][_j][_k].y() + hy);
        FNet[_i][_j + 1][_k].setZ(FNet[_i][_j][_k].z() + hz);
        break;
    case -10:
        FNet[_i][_j][_k + 1].setX(FNet[_i][_j][_k].x() + hx);
        FNet[_i][_j][_k + 1].setY(FNet[_i][_j][_k].y() + hy);
        FNet[_i][_j][_k + 1].setZ(FNet[_i][_j][_k].z() + hz);
        break;
    }
  // Обрабатываем остальные доп. точки
    for(int t = 1; t < Np-1; t++)
    {
        hx *= CoD;
        hy *= CoD;
        hz *= CoD;

        switch(mode)
        {
        case 1:
            FNet[_i+t+1][_j][_k].setX(FNet[_i+t][_j][_k].x() + hx);
            FNet[_i+t+1][_j][_k].setY(FNet[_i+t][_j][_k].y() + hy);
            FNet[_i+t+1][_j][_k].setZ(FNet[_i+t][_j][_k].z() + hz);
            break;
        case -1:
            FNet[_i][_j+t+1][_k].setX(FNet[_i][_j+t][_k].x() + hx);
            FNet[_i][_j+t+1][_k].setY(FNet[_i][_j+t][_k].y() + hy);
            FNet[_i][_j+t+1][_k].setZ(FNet[_i][_j+t][_k].z() + hz);
            break;
        case -10:
            FNet[_i][_j][_k+t+1].setX(FNet[_i][_j][_k+t].x() + hx);
            FNet[_i][_j][_k+t+1].setY(FNet[_i][_j][_k+t].y() + hy);
            FNet[_i][_j][_k+t+1].setZ(FNet[_i][_j][_k+t].z() + hz);
            break;
        }
    }
// Получили координаты линий на хорде
// II. Находим угол между получившимися прямыми
/*
Сначала определяем в какой плоскости лежит дуга


Направляющие векторы прямых: (ax, ay, az) & (bx, by, bz)
Угол между двумя прямыми:
                            cos(phi) = (ax*bx+ay*by+az*bz) / [ sqrt(ax^2+ay^2+az^2) * sqrt(ax^2+ay^2+az^2) ]
В качестве первой точки ВСЕГДА берем точку центра окружности.
Основная прямая - прямая, проходящая через центр и p1.
Вторая прямая - между центром и точкой на хорде.

Сначала смещаем точку в XY координатах:
cos(alpha) = x1/r;
sin(alpha) = y1/r;
cos(alpha+phi) = x2/r;
sin(alpha+phi) = y2/r;
(x1, y1) - координаты точки p1(перая точка крив. участка)
alpha - полярный угол p1
(x2, y2) - новая точка
phi - угол между прямыми center-p1 и center-новая точка в XY координатах
alpha+phi - полярный угол новой точки
Раскрываем уравнение как косинус/синус суммы, находим XY координаты новой точки

Z-координату находим через подобие треугольников
*/
    double cos_phi, sin_phi, radius;// угол между прямыми и радиус
    bool reverse = false;// флаг для отслеживания смены точек
// работа с доп. прямыми
    for(int t = 0; t < Np-1; t++)
    {
        switch(mode)
        {
        case 1:
            if(checkPlaneZ(p1, p2))// если окружность цилиндра в XY плоскости
            {
              // считаем угол в осях XY
                // косинус считаем по теореме косинусов
                cos_phi = cosXY(center, FNet[_i][_j][_k], FNet[_i+t+1][_j][_k]);
                sin_phi = sqrt(1 - cos_phi * cos_phi);
                radius = getLengthXY(p1, center);
                //if(placeOfPointXY(FNet[_i][_j][_k], FNet[_i+t+1][_j][_k], center) > 0)

                if(placeOfPointXY(p1, p2, center) > 0)
                {

                    FNet[_i+t+1][_j][_k].setX(center.x() + (cos_phi * (-center.x() + p1.x()) - sin_phi * (-center.y() + p1.y()) ));
                    FNet[_i+t+1][_j][_k].setY(center.y() + (cos_phi * (-center.y() + p1.y()) + sin_phi * (-center.x() + p1.x()) ));
                }
                else
                {

                    FNet[_i+t+1][_j][_k].setX(center.x() + (cos_phi * (-center.x() + p1.x()) + sin_phi * (-center.y() + p1.y()) ));
                    FNet[_i+t+1][_j][_k].setY(center.y() + (cos_phi * (-center.y() + p1.y()) - sin_phi * (-center.x() + p1.x()) ));
                }
                if(! p1.compareZ(p2))
                    FNet[_i+t+1][_j][_k].setZ( radius / (FNet[_i+t+1][_j][_k].z() * getLengthXY(center, FNet[_i+t+1][_j][_k])));
                else
                    FNet[_i+t+1][_j][_k].setZ(p1.z());
            }
            else
            if(checkPlaneY(p1, p2))// окружность цилиндра лежит в XZ плоскости
            {
                // считаем угол в осях XZ
                  cos_phi = cosXZ(center, FNet[_i][_j][_k], FNet[_i+t+1][_j][_k]);
                  sin_phi = sqrt(1 - cos_phi * cos_phi);
                  radius = getLengthXZ(p1, center);

                  if(placeOfPointXZ(p1, p2, center) > 0)
                  {

                      FNet[_i+t+1][_j][_k].setX(center.x() +  (cos_phi * (-center.x() + p1.x()) - sin_phi * (-center.z() + p1.z()) ));
                      FNet[_i+t+1][_j][_k].setZ(center.z() +  (cos_phi * (-center.z() + p1.z()) + sin_phi * (-center.x() + p1.x()) ));
                  }
                  else
                  {

                      FNet[_i+t+1][_j][_k].setX(center.x() +  (cos_phi * (-center.x() + p1.x()) + sin_phi * (-center.z() + p1.z()) ));
                      FNet[_i+t+1][_j][_k].setZ(center.z() +  (cos_phi * (-center.z() + p1.z()) - sin_phi * (-center.x() + p1.x()) ));
                  }
                  if(! p1.compareY(p2))
                      FNet[_i+t+1][_j][_k].setY( radius / (FNet[_i+t+1][_j][_k].y() * getLengthXZ(center, FNet[_i+t+1][_j][_k])));
                  else
                      FNet[_i+t+1][_j][_k].setY(p1.y());
            }
            break;
        case -1:
            if(checkPlaneZ(p1, p2))// если окружность цилиндра в XY плоскости
            {
              // считаем угол в осях XY
                cos_phi = cosXY(center, FNet[_i][_j][_k], FNet[_i][_j+t+1][_k]);
                sin_phi = sqrt(1 - cos_phi * cos_phi);
                radius = getLengthXY(p1, center);
                //if(placeOfPointXY(FNet[_i][_j][_k], FNet[_i][_j+t+1][_k], center) > 0)

                if(placeOfPointXY(p1, p2, center) > 0)
                {

                    FNet[_i][_j+t+1][_k].setX( center.x() +  (cos_phi * (-center.x() + p1.x()) - sin_phi * (-center.y() + p1.y()) ));
                    FNet[_i][_j+t+1][_k].setY( center.y() +  (cos_phi * (-center.y() + p1.y()) + sin_phi * (-center.x() + p1.x()) ));
                }
                else
                {

                    FNet[_i][_j+t+1][_k].setX( center.x() +  (cos_phi * (-center.x() + p1.x()) + sin_phi * (-center.y() + p1.y()) ));
                    FNet[_i][_j+t+1][_k].setY( center.y() +  (cos_phi * (-center.y() + p1.y()) - sin_phi * (-center.x() + p1.x()) ));
                }
                if(! p1.compareZ(p2))
                    FNet[_i][_j+t+1][_k].setZ( radius / (FNet[_i][_j+t+1][_k].z() * getLengthXY(center, FNet[_i][_j+t+1][_k])));
                else
                    FNet[_i][_j+t+1][_k].setZ(p1.z());
            }
            else
            if(checkPlaneX(p1, p2))// окружность цилиндра лежит в YZ плоскости
            {
                // считаем угол в осях YZ
                  cos_phi = cosYZ(center, FNet[_i][_j][_k], FNet[_i][_j+t+1][_k]);
                  sin_phi = sqrt(1 - cos_phi * cos_phi);
                  radius = getLengthYZ(p1, center);
                  //if(placeOfPointYZ(FNet[_i][_j][_k], FNet[_i][_j+t+1][_k], center) > 0)
                  if(placeOfPointYZ(p1, p2, center) > 0)
                  {

                      FNet[_i][_j+t+1][_k].setY( center.y() + (cos_phi * (-center.y() + p1.y()) - sin_phi * (-center.z() + p1.z()) ));
                      FNet[_i][_j+t+1][_k].setZ( center.z() + (cos_phi * (-center.z() + p1.z()) + sin_phi * (-center.y() + p1.y()) ));
                  }
                  else
                  {

                      FNet[_i][_j+t+1][_k].setY( center.y() + (cos_phi * (-center.y() + p1.y()) + sin_phi * (-center.z() + p1.z()) ));
                      FNet[_i][_j+t+1][_k].setZ( center.z() + (cos_phi * (-center.z() + p1.z()) - sin_phi * (-center.y() + p1.y()) ));
                  }
                  if(! p1.compareX(p2))
                      FNet[_i][_j+t+1][_k].setX( radius / (FNet[_i][_j+t+1][_k].x() * getLengthYZ(center, FNet[_i][_j+t+1][_k])));
                  else
                      FNet[_i][_j+t+1][_k].setX(p1.x());
            }
            break;
        case -10:
            if(checkPlaneY(p1, p2))// если окружность цилиндра в XZ плоскости
            {
              // считаем угол в осях XZ
                cos_phi = cosXZ(center, FNet[_i][_j][_k], FNet[_i][_j][_k+t+1]);
                sin_phi = sqrt(1 - cos_phi * cos_phi);
                radius = getLengthXZ(p1, center);
                //if(placeOfPointXZ(FNet[_i][_j][_k], FNet[_i][_j][_k+t+1], center) > 0)

                if(placeOfPointXZ(p1, p2, center) > 0)
                {

                    FNet[_i][_j][_k+t+1].setX( center.y() + (cos_phi * (-center.x() + p1.x()) - sin_phi * (-center.z() + p1.z())  ));
                    FNet[_i][_j][_k+t+1].setZ( center.z() + (cos_phi * (-center.z() + p1.z()) + sin_phi * (-center.x() + p1.x())  ));
                }
                else
                {

                    FNet[_i][_j][_k+t+1].setX( center.y() + (cos_phi * (-center.x() + p1.x()) + sin_phi * (-center.z() + p1.z())  ));
                    FNet[_i][_j][_k+t+1].setZ( center.z() + (cos_phi * (-center.z() + p1.z()) - sin_phi * (-center.x() + p1.x())  ));
                }
                if(! p1.compareY(p2))
                    FNet[_i][_j][_k+t+1].setY( radius / (FNet[_i][_j][_k+t+1].z() * getLengthXZ(center, FNet[_i][_j][_k+t+1])));
                else
                    FNet[_i][_j][_k+t+1].setY(p1.z());
            }
            else
            if(fabs(getLengthYZ(p1, center) - getLengthYZ(p2, center)))// окружность цилиндра лежит в YZ плоскости
            {
                // считаем угол в осях YZ
                  cos_phi = placeOfPointYZ(FNet[_i][_j][_k], FNet[_i][_j][_k+t+1], center) * cosYZ(center, FNet[_i][_j][_k], FNet[_i][_j][_k+t+1]);
                  sin_phi = sqrt(1 - cos_phi * cos_phi);
                  radius = getLengthYZ(p1, center);
                  //if(cos_phi > 0)

                  if(placeOfPointYZ(p1, p2, center) > 0)
                  {

                      FNet[_i][_j][_k+t+1].setY( center.y() + (cos_phi * (-center.y() + p1.y()) - sin_phi * (-center.z() + p1.z()) ));
                      FNet[_i][_j][_k+t+1].setZ( center.z() + (cos_phi * (-center.z() + p1.z()) + sin_phi * (-center.y() + p1.y()) ));
                  }
                  else
                  {

                      FNet[_i][_j][_k+t+1].setY( center.y() + (cos_phi * (-center.y() + p1.y()) + sin_phi * (-center.z() + p1.z()) ));
                      FNet[_i][_j][_k+t+1].setZ( center.z() + (cos_phi * (-center.z() + p1.z()) - sin_phi * (-center.y() + p1.y()) ));
                  }
                  if(! p1.compareX(p2))
                      FNet[_i][_j][_k+t+1].setX( radius / (FNet[_i][_j][_k+t+1].x() * getLengthYZ(center, FNet[_i][_j][_k+t+1])));
                  else
                      FNet[_i][_j][_k+t+1].setX(p1.x());
            }
            break;
        }
    }

}



void Net::curvilinearAccounting()
{
    QDPoint _buf1, _buf2, _center;// крайние точки кривол. участка + центр окружности
    Index3 _index1, _index2;
    int _t;

  // Выделяем память под массивы пар опорных элементов(см. инициализацию в net.h)
    int _i = 0, _j = 0, _k = 0;// счетчик пар опорных элементов, образующих кривол. участок
    OnX.resize(CL_X);
    for(int i = 0; i < CL_X; i++)
        OnX[i].resize(2);
    OnY.resize(CL_Y);
    for(int i = 0; i < CL_Y; i++)
        OnY[i].resize(2);
    OnZ.resize(CL_Z);
    for(int i = 0; i < CL_Z; i++)
        OnZ[i].resize(2);

    for(int m = 0; m < NCL; m++)// обрабатываем все криволин. участки
    {
        switch(int(CLSections[m][0]))
        {
        case 1:// если искривление по горизонтали (по оси X)
        // вычисляем индексы крайних точек в р. сетке
          // индекс по Z
            _index1.k = 0;
            for(_t = 0; _t < CLSections[m][1] - 1; _t++)
                _index1.k += ZSegments[_t];
            _index2.k = _index1.k;
          // индекс по X
            _index1.i = 0;
            for(_t = 0; _t < CLSections[m][3] - 1; _t++)// сдвигаемся по оси X в нужный узел
                _index1.i += XSegments[_t];
            _index2.i = _index1.i + XSegments[_t];
          // индекс по Y
            _index1.j = 0;
            for(_t = 0; _t < CLSections[m][2] - 1; _t++)// сдвигаемся по оси Y в нужный узел
                 _index1.j += YSegments[_t];
             _index2.j =  _index1.j;

          // сохраняем индексы
             OnX[_i][0] = _index1;
             OnX[_i][1] = _index2;
             _i++;
          // сохраняем точки
            _buf1 = FNet[_index1.i][_index1.j][_index1.k];
            _buf2 = FNet[_index2.i][_index2.j][_index2.k];
            _center.setX(CLSections[m][4]);
            _center.setY(CLSections[m][5]);
            _center.setZ(CLSections[m][6]);
          // Вычисляем доп. точки
            calcPointOnCL(_buf1, _buf2, _center, XSegments[CLSections[m][2] - 1], XCoD[CLSections[m][2] - 1],
                    _index1, _index2, CLSections[m][0]);
            break;
        case -1:// если искривление по вертикали (по оси Y)
            // вычисляем индексы крайних точек в р. сетке
              // индекс по Z
            _index1.k = 0;
            for(_t = 0; _t < CLSections[m][1] - 1; _t++)
                _index1.k += ZSegments[_t];
            _index2.k = _index1.k;
              // индекс по X
                _index1.i = 0;
                for(_t = 0; _t < CLSections[m][3] - 1; _t++)// сдвигаемся по оси Y в нужный узел
                    _index1.i += XSegments[_t];
                _index2.i = _index1.i;
              // индекс по Y
                _index1.j = 0;
                for(_t = 0; _t < CLSections[m][2] - 1; _t++)// сдвигаемся по оси X в нужный узел
                     _index1.j += YSegments[_t];
                 _index2.j =  _index1.j + YSegments[_t];
              // сохраняем индексы
                 OnY[_j][0] = _index1;
                 OnY[_j][1] = _index2;
                 _j++;
              // сохраняем точки
                _buf1 = FNet[_index1.i][_index1.j][_index1.k];
                _buf2 = FNet[_index2.i][_index2.j][_index2.k];
                _center.setX(CLSections[m][4]);
                _center.setY(CLSections[m][5]);
                _center.setZ(CLSections[m][6]);
              // Вычисляем доп. точки
                calcPointOnCL(_buf1, _buf2, _center, YSegments[CLSections[m][2] - 1], YCoD[CLSections[m][2] - 1],
                        _index1, _index2, CLSections[m][0]);
            break;
        case -10:// если искривление по оси Z
            // вычисляем индексы крайних точек в р. сетке
              // индекс по Z
            _index1.k = 0;
            for(_t = 0; _t < CLSections[m][0] - 1; _t++)
                _index1.k += ZSegments[_t];
            _index2.k = _index1.k + ZSegments[_t];

            _index1.i = 0;
            for(_t = 0; _t < CLSections[m][3] - 1; _t++)// сдвигаемся по оси X в нужный узел
                _index1.i += XSegments[_t];
            _index2.i = _index1.i;
            _index1.j = 0;
            for(_t = 0; _t < CLSections[m][2] - 1; _t++)// сдвигаемся по оси Y в нужный узел
                _index1.j += XSegments[_t];
            _index2.j = _index1.j;
            // сохраняем индексы
            OnZ[_k][0] = _index1;
            OnZ[_k][1] = _index2;
            _k++;
            // сохраняем точки
              _buf1 = FNet[_index1.i][_index1.j][_index1.k];
              _buf2 = FNet[_index2.i][_index2.j][_index2.k];
              _center.setX(CLSections[m][4]);
              _center.setY(CLSections[m][5]);
              _center.setZ(CLSections[m][6]);
              // Вычисляем доп. точки
              calcPointOnCL(_buf1, _buf2, _center, YSegments[CLSections[m][2] - 1], YCoD[CLSections[m][2] - 1],
                      _index1, _index2, CLSections[m][0]);

            break;
        default:
            qDebug() << "Ошибка: Некорректный номер признака искривления! (Должен быть 1, -1, -10)";
            break;
        }

    }
}

/*
Раздробленная сетка
*/

void Net::allocation()
{
    Nx = Ny = Nz = 0;
// Выделение памяти под раздробленную сетку
    for(int i = 0; i < XSegments.size(); i++)// по оси X
        Nx += XSegments[i];
    Nx++;
    FNet.resize(Nx);

    for(int i = 0; i < YSegments.size(); i++)// по оси Y
        Ny += YSegments[i];
    Ny++;
    for(int i = 0; i < FNet.size(); i++)
        FNet[i].resize(Ny);

    for(int i = 0; i < ZSegments.size(); i++)// по оси Z
        Nz += ZSegments[i];
    Nz++;
    for(int i = 0; i < FNet.size(); i++)
        for(int j = 0; j < FNet[i].size(); j++)
            FNet[i][j].resize(Nz);

// Выделение памяти под массив индексов опорных точек
        IndexOfRefPoints.resize(Nwx);
        for(int i = 0; i < Nwx; i++)
        {
            IndexOfRefPoints[i].resize(Nwy);
            for(int j = 0; j < Nwy; j++)
                IndexOfRefPoints[i][j].resize(Nwz);
        }

// Высчитываем индексы опорных узлов в р. сетке
    for(int k = 0; k < Nwz; k++)
    for(int j = 0; j < Nwy; j++)
    for(int i = 0; i < Nwx; i++)
    {
        IndexOfRefPoints[i][j][k].i = 0;
        for(int t = 0; t < i; t++)
            IndexOfRefPoints[i][j][k].i += XSegments[t];

        IndexOfRefPoints[i][j][k].j = 0;
        for(int t = 0; t < j; t++)
            IndexOfRefPoints[i][j][k].j += YSegments[t];

        IndexOfRefPoints[i][j][k].k = 0;
        for(int t = 0; t < k; t++)
            IndexOfRefPoints[i][j][k].k += ZSegments[t];
        // Вносим координаты опорных точек в раздробленную сетку
        FNet[IndexOfRefPoints[i][j][k].i][IndexOfRefPoints[i][j][k].j][IndexOfRefPoints[i][j][k].k] = RefPoints[i][j][k];
    }


}

void Net::calcPointOnSegments()
{
/*
Сначала высчитываем координаты точек на отрезках между опорными элементами,
которые не образуют кривол. часть. Затем, зная координаты концов отрезка, расставляем оставшиеся.
*/
  // Обрабатываем отрезки между опорными по Ox
    for(int k = 0; k < Nwz; k++)
    for(int j = 0; j < Nwy; j++)
    for(int i = 0; i < Nwx - 1; i++)
    {
        if(!isRPointsOnCL(IndexOfRefPoints[i][j][k], IndexOfRefPoints[i+1][j][k], 1))// если опорные точки не лежат на кривол. участке
        {
           // первая и последняя точка в отрезке
           Index3 _iBegin = IndexOfRefPoints[i][j][k];
           Index3 _iEnd = IndexOfRefPoints[i+1][j][k];
           // вычисляем значение начального шага
           double _hx, _hy, _hz;
           _hx = getLengthX(FNet[_iBegin.i][_iBegin.j][_iBegin.k], FNet[_iEnd.i][_iEnd.j][_iEnd.k]);
           _hx *= (1 - XCoD[i]) / (1 - pow(XCoD[i], XSegments[i]));

           _hy = getLengthX(FNet[_iBegin.i][_iBegin.j][_iBegin.k], FNet[_iEnd.i][_iEnd.j][_iEnd.k]);
           _hy *= (1 - XCoD[i]) / (1 - pow(XCoD[i], XSegments[i]));

           _hz = getLengthX(FNet[_iBegin.i][_iBegin.j][_iBegin.k], FNet[_iEnd.i][_iEnd.j][_iEnd.k]);
           _hz *= (1 - XCoD[i]) / (1 - pow(XCoD[i], XSegments[i]));

           FNet[_iBegin.i+1][_iBegin.j][_iBegin.k].setX(FNet[_iBegin.i+1][_iBegin.j][_iBegin.k].x() + _hx);//тут иправил .x() не было
           FNet[_iBegin.i+1][_iBegin.j][_iBegin.k].setY(FNet[_iBegin.i+1][_iBegin.j][_iBegin.k].y() + _hy);
           FNet[_iBegin.i+1][_iBegin.j][_iBegin.k].setZ(FNet[_iBegin.i+1][_iBegin.j][_iBegin.k].z() + _hz);

           for(int t = 1; t < XSegments[i] - 1; t++)
           {
               _hx *= XCoD[i];
               _hy *= XCoD[i];
               _hz *= XCoD[i];

               FNet[_iBegin.i+t+1][_iBegin.j][_iBegin.k].setX(FNet[_iBegin.i+t][_iBegin.j][_iBegin.k].x() + _hx);//тут иправил .x() не было
               FNet[_iBegin.i+t+1][_iBegin.j][_iBegin.k].setY(FNet[_iBegin.i+t][_iBegin.j][_iBegin.k].y() + _hy);
               FNet[_iBegin.i+t+1][_iBegin.j][_iBegin.k].setZ(FNet[_iBegin.i+t][_iBegin.j][_iBegin.k].z() + _hz);
           }
        }
    }

    // Обрабатываем отрезки между опорными по Oy
      for(int k = 0; k < Nwz; k++)
      for(int i = 0; i < Nwx; i++)
      for(int j = 0; j < Nwy - 1; j++)
      {
          if(!isRPointsOnCL(IndexOfRefPoints[i][j][k], IndexOfRefPoints[i][j+1][k], -1))// если опорные точки не лежат на кривол. участке
          {
             // первая и последняя точка в отрезке
             Index3 _iBegin = IndexOfRefPoints[i][j][k];
             Index3 _iEnd = IndexOfRefPoints[i][j+1][k];
             // вычисляем значение начального шага
             double _hx, _hy, _hz;
             _hx = getLengthY(FNet[_iBegin.i][_iBegin.j][_iBegin.k], FNet[_iEnd.i][_iEnd.j][_iEnd.k]);
             _hx *= (1 - YCoD[j]) / (1 - pow(YCoD[j], YSegments[j]));

             _hy = getLengthY(FNet[_iBegin.i][_iBegin.j][_iBegin.k], FNet[_iEnd.i][_iEnd.j][_iEnd.k]);
             _hy *= (1 - YCoD[j]) / (1 - pow(YCoD[j], YSegments[j]));

             _hz = getLengthZ(FNet[_iBegin.i][_iBegin.j][_iBegin.k], FNet[_iEnd.i][_iEnd.j][_iEnd.k]);
             _hz *= (1 - ZCoD[j]) / (1 - pow(YCoD[j], YSegments[j]));

             FNet[_iBegin.i][_iBegin.j+1][_iBegin.k].setX(FNet[_iBegin.i][_iBegin.j][_iBegin.k].x() + _hx);
             FNet[_iBegin.i][_iBegin.j+1][_iBegin.k].setY(FNet[_iBegin.i][_iBegin.j][_iBegin.k].y() + _hy);
             FNet[_iBegin.i][_iBegin.j+1][_iBegin.k].setZ(FNet[_iBegin.i][_iBegin.j][_iBegin.k].z() + _hz);

             for(int t = 1; t < YSegments[j] - 1; t++)
             {
                 _hx *= YCoD[j];
                 _hy *= YCoD[j];
                 _hz *= YCoD[j];

                 FNet[_iBegin.i][_iBegin.j+t+1][_iBegin.k].setX(FNet[_iBegin.i][_iBegin.j+t][_iBegin.k].x() + _hx);
                 FNet[_iBegin.i][_iBegin.j+t+1][_iBegin.k].setY(FNet[_iBegin.i][_iBegin.j+t][_iBegin.k].y() + _hy);
                 FNet[_iBegin.i][_iBegin.j+t+1][_iBegin.k].setZ(FNet[_iBegin.i][_iBegin.j+t][_iBegin.k].z() + _hz);
             }
          }
      }

      // Обрабатываем отрезки между опорными по Oz
        for(int i = 0; i < Nwx; i++)
        for(int j = 0; j < Nwy; j++)
        for(int k = 0; k < Nwz - 1; k++)
        {
            if(!isRPointsOnCL(IndexOfRefPoints[i][j][k], IndexOfRefPoints[i][j][k+1], -10))// если опорные точки не лежат на кривол. участке
            {
               // первая и последняя точка в отрезке
               Index3 _iBegin = IndexOfRefPoints[i][j][k];
               Index3 _iEnd = IndexOfRefPoints[i][j][k+1];
               // вычисляем значение начального шага
               double _hx, _hy, _hz;
               _hx = getLengthZ(FNet[_iBegin.i][_iBegin.j][_iBegin.k], FNet[_iEnd.i][_iEnd.j][_iEnd.k]);
               _hx *= (1 - ZCoD[k]) / (1 - pow(ZCoD[k], ZSegments[k]));

               _hy = getLengthZ(FNet[_iBegin.i][_iBegin.j][_iBegin.k], FNet[_iEnd.i][_iEnd.j][_iEnd.k]);
               _hy *= (1 - ZCoD[k]) / (1 - pow(ZCoD[k], ZSegments[k]));

               _hz = getLengthZ(FNet[_iBegin.i][_iBegin.j][_iBegin.k], FNet[_iEnd.i][_iEnd.j][_iEnd.k]);
               _hz *= (1 - ZCoD[k]) / (1 - pow(ZCoD[k], ZSegments[k]));

               FNet[_iBegin.i][_iBegin.j][_iBegin.k+1].setX(FNet[_iBegin.i][_iBegin.j][_iBegin.k].x() + _hx);
               FNet[_iBegin.i][_iBegin.j][_iBegin.k+1].setY(FNet[_iBegin.i][_iBegin.j][_iBegin.k].y() + _hy);
               FNet[_iBegin.i][_iBegin.j][_iBegin.k+1].setZ(FNet[_iBegin.i][_iBegin.j][_iBegin.k].z() + _hz);

               for(int t = 1; t < ZSegments[k] - 1; t++)
               {
                   _hx *= ZCoD[k];
                   _hy *= ZCoD[k];
                   _hz *= ZCoD[k];

                   FNet[_iBegin.i][_iBegin.j][_iBegin.k+t+1].setX(FNet[_iBegin.i][_iBegin.j][_iBegin.k+t].x() + _hx);
                   FNet[_iBegin.i][_iBegin.j][_iBegin.k+t+1].setY(FNet[_iBegin.i][_iBegin.j][_iBegin.k+t].y() + _hy);
                   FNet[_iBegin.i][_iBegin.j][_iBegin.k+t+1].setZ(FNet[_iBegin.i][_iBegin.j][_iBegin.k+t].z() + _hz);
               }
            }
        }

        // Обрабатываем точки, не лежащие на отрезках, образованные опорными точками


}

bool Net::isRPointsOnCL(Index3 i1, Index3 i2, int mode)
{
    switch(mode)
    {
    case 1:
        for(int i = 0; i < OnX.size(); i++)// не было оператора равнения
        {
            if( (i1 == OnX[i][0] && i2 == OnX[i][1]) ||
                (i2 == OnX[i][0] && i1 == OnX[i][1]) )
                return true;
        }
        return false;
        break;
    case -1:
        for(int i = 0; i < OnY.size(); i++)
        {
            if( (i1 == OnY[i][0] && i2 == OnY[i][1]) ||
                (i2 == OnY[i][0] && i1 == OnY[i][1]) )
                return true;
        }
        return false;
        break;
    case -10:
        for(int i = 0; i < OnZ.size(); i++)
        {
            if( (i1 == OnZ[i][0] && i2 == OnZ[i][1]) ||
                (i2 == OnZ[i][0] && i1 == OnZ[i][1]) )
                return true;
        }
        return false;
        break;
    }
}

QDPoint Net::getFNet(int i, int j, int k)
{
    return FNet[i][j][k];
}

int Net::getGlobalId(int i, int j, int k)
{
    return i + j * Nx + k * Nx * Ny;
}

int Net::sizeX()
{
    return Nx;
}
int Net::sizeY()
{
    return Ny;
}
int Net::sizeZ()
{
    return Nz;
}

/*
Остальное
*/

void Net::createNet(QString& dir)
{
    QString str = dir + "/NetInfo.txt";
    loadInfoFromFile(str);
    allocation();// выделяем память под элементы, подсчитываем индексы опорных точек в сетке
    curvilinearAccounting();// генерируем точки на кривол. участках
    calcPointOnSegments();// генерируем точки на отрезках между опорными точками (не кривол.)
}

void Net::loadInfoFromFile(QString& filename)
{
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        QString bufString;
        double bufDouble;

    //Считывание числа опорных точек по координатам
        in >> bufString;// "Количество_опорных_точек_по_координатам"
        in >> Nwx >> Nwy >> Nwz;
        NAll = Nwx * Nwy * Nwz;

    //Выделение памяти под опорные точки
        RefPoints.resize(Nwx);
        for(int i = 0; i < Nwx; i++)
        {
            RefPoints[i].resize(Nwy);
            for(int j = 0; j < Nwy; j++)
                RefPoints[i][j].resize(Nwz);
        }

    //Считывание опорных точек
        in >> bufString;// "Опорные_точки"
        for(int k = 0; k < Nwz; k++)
        for(int j = 0; j < Nwy; j++)
        for(int i = 0; i < Nwx; i++)
        {
            in >> bufDouble; RefPoints[i][j][k].setX(bufDouble);
            in >> bufDouble; RefPoints[i][j][k].setY(bufDouble);
            in >> bufDouble; RefPoints[i][j][k].setZ(bufDouble);

        }
    //Считывание информации о разбиении сетки
        in >> bufString;// "Информация_о_разбиении"
        XSegments.resize(Nwx - 1); XCoD.resize(Nwx - 1);
        for(int i = 0; i < Nwx - 1; i++)
        {
            in >> XSegments[i];
            in >> XCoD[i];
        }
        YSegments.resize(Nwy - 1); YCoD.resize(Nwy - 1);
        for(int i = 0; i < Nwy - 1; i++)
        {
            in >> YSegments[i];
            in >> YCoD[i];
        }
        ZSegments.resize(Nwz - 1); ZCoD.resize(Nwz - 1);
        for(int i = 0; i < Nwz - 1; i++)
        {
            in >> ZSegments[i];
            in >> ZCoD[i];
        }
    //Считывание информации о подобластях
        in >> bufString;// "Число_подобластей"
        in >> Nw;
        in >> bufString;// "Номер_и_границы_подобластей"
        Subareas.resize(Nw);
        for(int i = 0; i < Nw; i++)
        {
            Subareas[i].resize(7);
            for(int j = 0; j < 7; j++)
                in >> Subareas[i][j];
        }

    //Считывание информации о криволинейных участках
        in >> bufString;// "Информация_о_криволинейных_участках"
        in >> NCL;
        CLSections.resize(NCL);
        for(int i = 0; i < NCL; i++)
        {
            CLSections[i].resize(7);
            for(int j = 0; j < 7; j++)
                in >> CLSections[i][j];
        }
    // Сортируем информацию о кривол. участках
    // Сначала по X, Y, Z искривлениям, внутри каждой подгруппы по уровням по Z
        CL_X = 0, CL_Y = 0, CL_Z = 0;
    // Считаем кол-во искривлений по каждой из осей
        for(int i = 0; i < NCL; i++)
        {
            switch(int(CLSections[i][0])) // на самом деле хз как оно будет работать, допустим дабл 1 это 0.999999 и в инт приедется как 0, но тут мб подругому
            {
                case 1:
                    CL_X++;
                    break;
                case -1:   // нельзя отрицательные числа
                    CL_Y++;
                    break;
                case -10:
                    CL_Z++;
                    break;
            }
        }

    // Сортируем по X, Y, Z (первый элемент в массивах)
        for(int i = 0; i < NCL - 1; i++)
        {
            for(int j = i+1; j > i; j--)
            {
                if(CLSections[j][0] > CLSections[j-1][0])
                    CLSections[j].swap(CLSections[j-1]);
            }
        }
    // Сортируем по уровню Z в каждой из групп
        for(int i = 0; i < CL_X - 1; i++)
        {
            for(int j = i+1; j > i; j--)
            {
                if(CLSections[j][1] < CLSections[j-1][1])
                    CLSections[j].swap(CLSections[j-1]);
            }
        }

        for(int i = CL_X; i < CL_X + CL_Y - 1; i++)
        {
            for(int j = i+1; j > i; j--)
            {
                if(CLSections[j][1] < CLSections[j-1][1])
                    CLSections[j].swap(CLSections[j-1]);
            }
        }

        for(int i = CL_X + CL_Y; i < NCL - 1; i++)
        {
            for(int j = i+1; j > i; j--)
            {
                if(CLSections[j][1] < CLSections[j-1][1])
                    CLSections[j].swap(CLSections[j-1]);
            }
        }

    }
}



