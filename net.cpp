#include "net.h"
#include "geometry.h"

Net::Net()
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
    lengthX = getLengthX(p1, p2);
    lengthY = getLengthY(p1, p2);
    lengthZ = getLengthZ(p1, p2);
  // Вычисляем величину начального шага
    hx = lengthX * ((1-CoD)/pow(1-Cod, Np));
    hy = lengthY * ((1-CoD)/pow(1-Cod, Np));
    hz = lengthZ * ((1-CoD)/pow(1-Cod, Np));
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
    double ax, ay, az, bx, by, bz; // элементы направляющих векторов
    double cos_phi, sin_phi, radius;// угол между прямыми и радиус
// основная прямая
    ax = center.x() - FNet[_i][_j][_k].x();
    ay = center.y() - FNet[_i][_j][_k].y();
    az = center.z() - FNet[_i][_j][_k].z();
// работа с доп. прямыми
    for(int t = 0; t < Np-1; t++)
    {
        switch(mode)
        {
        case 1:
            bx = center.x() - FNet[_i+t+1][_j][_k].x();
            by = center.y() - FNet[_i+t+1][_j][_k].y();
            bz = center.z() - FNet[_i+t+1][_j][_k].z();
          // считаем угол в осях XY
            cos_phi = (ax*bx+ay*by) / ( sqrt(ax*ax+ay*ay) * sqrt(bx*bx+by*by) );
            sin_phi = sqrt(1 - cos_phi * cos_phi);
            radius = getLengthXY(p1, center);
            FNet[_i+t+1][_j][_k].setX( (cos_phi * p1.x() - sin_phi * p1.y()) / radius );
            FNet[_i+t+1][_j][_k].setY( (cos_phi * p1.y() + sin_phi * p1.x()) / radius );
            FNet[_i+t+1][_j][_k].setZ( radius / (FNet[_i+t+1][_j][_k].z() * getLengthXY(center, FNet[_i+t+1][_j][_k])));
            break;
        case -1:
            bx = center.x() - FNet[_i][_j+t+1][_k].x();
            by = center.y() - FNet[_i][_j+t+1][_k].y();
            bz = center.z() - FNet[_i][_j+t+1][_k].z();

          // считаем угол в осях XY
            cos_phi = (ax*bx+ay*by) / ( sqrt(ax*ax+ay*ay) * sqrt(bx*bx+by*by) );
            sin_phi = sqrt(1 - cos_phi * cos_phi);
            radius = getLengthXY(p1, center);
            FNet[_i+t+1][_j][_k].setX( (cos_phi * p1.x() - sin_phi * p1.y()) / radius );
            FNet[_i+t+1][_j][_k].setY( (cos_phi * p1.y() + sin_phi * p1.x()) / radius );
            FNet[_i+t+1][_j][_k].setZ( radius / (FNet[_i][_j+t+1][_k].z() * getLengthXY(center, FNet[_i][_j+t+1][_k])));
            break;
        case -10:
            bx = center.x() - FNet[_i][_j][_k+t+1].x();
            by = center.y() - FNet[_i][_j][_k+t+1].y();
            bz = center.z() - FNet[_i][_j][_k+t+1].z();
            break;
        }
    }

}

void Net::curvilinearAccounting()
{
    QDPoint _buf1, _buf2, _center;// крайние точки кривол. участка + центр окружности
    Index3 _index1, _index2;
    int _i1, _j1, _i2, _j2, _k, _t;
    for(int m = 0; m < NCL; m++)// обрабатываем все криволин. участки
    {
        switch(int(CLSections[m][0]))
        {
        case 1:// если искривление по горизонтали (по оси X)
        // вычисляем индексы крайних точек в р. сетке
          // индекс по Z
            _index1.k = _index2.k = CLSections[m][1] - 1;// уровень по Z - 1
          // индекс по X
            _index1.i = 0;
            for(_t = 0; _t < CLSections[m][2] - 1; _t++)// сдвигаемся по гориз. оси в нужный узел
                _index1.i += XSegments[_t];
            _index2.i = _index1.i + XSegments[_t];
          // индекс по Y
            _index1.j = 0;
            for(_t = 0; _t < CLSections[m][1] - 1; _t++)// сдвигаемся по вертик. оси в нужный узел
                 _index1.j += YSegments[_t];
             _index2.j =  _index1.j;
          // сохраняем точки
            _buf1 = FNet[_index1.i][_index1.j][_index1.k];
            _buf2 = FNet[_index2.i][_index2.j][_index2.k];
            _center.setX(CLSections[m][4]);
            _center.setY(CLSections[m][5]);
            _center.setZ(CLSections[m][6]);
          // Вычисляем доп. точки
            calcPointOnCL(_buf1, _buf2, _center, XSegments[CLSections[m][2] - 1], XCod[CLSections[m][2] - 1], _index1, _index2, CLSections[m][0]);
            break;
        case -1:// если искривление по вертикали (по оси Y)
            // вычисляем индексы крайних точек в р. сетке
              // индекс по Z
                _index1.k = _index2.k = CLSections[m][1] - 1;// уровень по Z - 1
              // индекс по X
                _index1.i = 0;
                for(_t = 0; _t < CLSections[m][1] - 1; _t++)// сдвигаемся по гориз. оси в нужный узел
                    _index1.i += XSegments[_t];
                _index2.i = _index1.i + XSegments[_t];
              // индекс по Y
                _index1.j = 0;
                for(_t = 0; _t < CLSections[m][2] - 1; _t++)// сдвигаемся по вертик. оси в нужный узел
                     _index1.j += YSegments[_t];
                 _index2.j =  _index1.j;
              // сохраняем точки
                _buf1 = FNet[_index1.i][_index1.j][_index1.k];
                _buf2 = FNet[_index2.i][_index2.j][_index2.k];
                _center.setX(CLSections[m][4]);
                _center.setY(CLSections[m][5]);
                _center.setZ(CLSections[m][6]);
              // Вычисляем доп. точки
                calcPointOnCL(_buf1, _buf2, _center, YSegments[CLSections[m][2] - 1], YCod[CLSections[m][2] - 1], _index1, _index2, CLSections[m][0]);
            break;
        case -10:// если искривление по оси Z
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

void Net::createNet()
{
    allocation();// выделяем память под элементы, подсчитываем индексы опорных точек в сетке
}

void Net::loadInfoFromFile(QString& filename)
{
    QFile file(filename);
    QTextStream in(&file);
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
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

    }
}



