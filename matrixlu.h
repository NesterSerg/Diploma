#ifndef MATRIXLU_H
#define MATRIXLU_H
#include<QVector>
#include "operators.h"

class MatrixLU
{
    public:
        MatrixLU(unsigned int size);
        //возвращают ссылки на элементы векторов ( можно редактировать элементы)
        int& rig(int i);
        int& rjg(int i);
        double& rdi(int i);
        double& rggl(int i);
        double& rggu(int i);
        double& rD(int i);
        double& rL(int i);
        double& rU(int i);
        //возвращают копии элементов
        int cig(int i)const;
        int cjg(int i)const;
        double cdi(int i)const;
        double cggl(int i)const;
        double cggu(int i)const;
        double cD(int i)const;
        double cL(int i)const;
        double cU(int i)const;
        friend const QVector<double> operator*(const MatrixLU &matrix, const QVector<double> &vector);// умножение не фактаризованной матрицы!! надо уточнить
        int size()const;
    private:
       unsigned int N;// размерность матрицы
       // ПОРТРЕТ МАТРИЦЫ
       QVector<int>ig;
       QVector<int>jg;
       //ЭЛЕМЕНТЫ МАТРИЦЫ
       QVector<double> di;// диагональ исходной матрицы
       QVector<double> ggl;// нижний треугольник исходной матрицы
       QVector<double> ggu;// верхний треугольник исходной матрицы
       //ЭЛЕМЕНТЫ ОБУСЛОВЛЕННОЙ МАТРИЦЫ
       QVector<double> D;// диагональ исходной матрицы
       QVector<double> L;// нижний треугольник исходной матрицы
       QVector<double> U;// верхний треугольник исходной матрицы
       //LU ФАКТОРИЗАЦИЯ
       double sm(int i, int j);
    public:
       void decomposition_LU();

};
#endif // MATRIXLU_H
