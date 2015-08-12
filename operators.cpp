#include "operators.h"
QVector<double>& operator+=(QVector<double> &vec1 , QVector<double> &vec2)
    {
        if(vec1.size() != vec2.size())
            qDebug()<< "operator '+=': vectors have different dimensions";
        else
        {
            unsigned int size = vec1.size();
            for(unsigned int i = 0; i < size; i++)
                vec1[i] += vec2[i];
        }
        return vec1;
    }
QVector<double>& operator-=(QVector<double> &vec1 , QVector<double> &vec2)
    {
        if(vec1.size() != vec2.size())
            qDebug()<< "operator '-=': vectors have different dimensions";
        else
        {
            unsigned int size = vec1.size();
            for(unsigned int i = 0; i < size; i++)
                vec1[i] -= vec2[i];
        }
        return vec1;
    }
QVector<double>& operator*=(QVector<double> &vec1, double factor)
    {
        unsigned int size = vec1.size();
        for(unsigned int i = 0; i < size; i++)
                vec1[i] *= factor;
            return vec1;
    }
QVector<double>& operator/=(QVector<double> &vec1, double divisor)
    {
        if(divisor == 0)
            qDebug() << "operator '/=': division by zero";
        else
        {
            unsigned int size = vec1.size();
            for(unsigned int i = 0; i < size; i++)
                vec1[i] /= divisor;
        }
            return vec1;
    }
//-----------------------------------------------------------------------------------------------------------
QVector<double> operator+(const QVector<double> &vec1, const QVector<double> &vec2)
    {
        QVector<double> vec3 = vec1;
        if(vec1.size() != vec2.size())
            qDebug()<< "operator '+': vectors have different dimensions";
        else
        {
            unsigned int size = vec1.size();
            for(unsigned int i = 0; i < size; i++)
                vec3[i] = vec1[i] + vec2[i];
        }
        return vec3;
    }
QVector<double> operator-(const QVector<double> &vec1, const QVector<double> &vec2)
    {
        QVector<double> vec3 = vec1;
        if(vec1.size() != vec2.size())
            qDebug()<< "operator '-': vectors have different dimensions";
        else
        {
            unsigned int size = vec1.size();
            for(unsigned int i = 0; i < size; i++)
                vec3[i] = vec1[i] - vec2[i];
        }
        return vec3;
    }
double operator*(const QVector<double> &vec1, const QVector<double> &vec2)// скалярное умножение
    {
        double res = 0.;
        if(vec1.size() != vec2.size())
            qDebug()<< "operator '*': vectors have different dimensions";
        else
        {
            unsigned int size = vec1.size();
            for(unsigned int i = 0; i < size; i++)
               res += vec1[i] * vec2[i];
        }
        return res;
    }
QVector<double> operator*(const QVector<double> &vec1, double factor)
    {
        QVector<double> vec2 = vec1;
        unsigned int size = vec1.size();
        for(unsigned int i = 0; i < size; i++)
            vec2[i] *=  factor;
        return vec2;
    }
QVector<double> operator*(double factor, const QVector<double> &vec1)
    {
        QVector<double> vec2 = vec1;
        unsigned int size = vec1.size();
        for(unsigned int i = 0; i < size; i++)
            vec2[i] *=  factor;
        return vec2;
    }
QVector<double> operator/(const QVector<double> &vec1, double divisor)
    {
        QVector<double> vec2 = vec1;
        if(divisor == 0)
            qDebug() << "operator '/': division by zero";
        else
        {
            unsigned int size = vec1.size();
            for(unsigned int i = 0; i < size; i++)
                vec2[i] /=  divisor;
        }
        return vec2;
    }
