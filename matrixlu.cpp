#include "matrixlu.h"

MatrixLU::MatrixLU(unsigned int size)
{
    N = size;
    di.resize(N);
    D.resize(N);
}

int &MatrixLU::rig(int i)
{
    return ig[i];
}

int &MatrixLU::rjg(int i)
{
    return jg[i];
}

double &MatrixLU::rdi(int i)
{
    return di[i];
}
double &MatrixLU:: rggl(int i)
{
    return ggl[i];
}

double &MatrixLU:: rggu(int i)
{
    return ggu[i];
}

double &MatrixLU:: rD(int i)
{
    return D[i];
}

double &MatrixLU:: rL(int i)
{
    return L[i];
}

double &MatrixLU:: rU(int i)
{
    return U[i];
}

int MatrixLU::cig(int i)const
{
    return ig[i];
}
int MatrixLU::cjg(int i)const
{
    return jg[i];
}
double MatrixLU::cdi(int i)const
{
    return di[i];
}
double MatrixLU::cggl(int i)const
{
    return ggl[i];
}
double MatrixLU::cggu(int i)const
{
    return ggu[i];
}
double MatrixLU::cD(int i)const
{
    return D[i];
}
double MatrixLU::cL(int i)const
{
    return L[i];
}
double MatrixLU::cU(int i)const
{
    return U[i];
}

int MatrixLU::size()const
{
    return N;
}
double MatrixLU::sm(int i, int j)
{
    int k, l, find;
    double result = 0.0;
    if (i == j)
       for (k = ig[i]; k < ig[i + 1]; k++)
        result += U[k] * L[k];
     else
     {
        // верхний треугольник
        if (i>j)
        {
            for (k = ig[j]; k < ig[j + 1]; k++)
            {
               find = 0;
               for (l = ig[i]; l < ig[i + 1] && find == 0; l++)
               {
                    if (jg[l] == jg[k])
                    {
                        result += U[k] * L[l];
                        find = 1;
                    }
               }
             }
         }
         // нижний треугольник
         else
         {
             for (l = ig[i]; l < ig[i + 1]; l++)
             {
                 find = 0;
                 for (k = ig[j]; k < ig[j + 1] && find == 0; k++)
                 {
                     if (jg[l] == jg[k])
                     {
                         result += U[k] * L[l];
                         find = 1;
                     }
                 }
             }
          }

    }
    return result;
}

void MatrixLU::decomposition_LU()
{
    for (int i = 0; i < N; i++)
        {
            for (int j = ig[i]; j < ig[i + 1]; j++)
            {
                L[j] = (ggl[j] - sm(i, jg[j]));
                U[j] = (ggu[j] - sm(jg[j], i)) / D[jg[j]];
            }
            D[i] = di[i] - sm(i, i);
        }
}

const QVector<double> operator*(const MatrixLU &matrix, const QVector<double> &vector)
{

    int i, j;
    int N = vector.size();
    QVector<double> res;
    res.resize(N);
    if(matrix.size() != vector.size())
        qDebug()<< "operator '*': vector and matrix have different dimensions";
    else
    {
        for (i = 0; i < N; i++)
        {
            res[i] = matrix.cdi(i) * vector[i];
            for (j = matrix.cig(i); j < matrix.cig(i + 1); j++)
            {
                res[i] += matrix.cggl(j) * vector[matrix.cjg(j)];
                res[matrix.cjg(j)] += matrix.cggu(j) * vector[i];
            }
        }
    }

    return res;

}

