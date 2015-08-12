#ifndef OPERATORS
#define OPERATORS
#include <QVector>
#include <QDebug>
QVector<double>& operator+=(QVector<double> &vec1 , QVector<double> &vec2);

QVector<double>& operator-=(QVector<double> &vec1 , QVector<double> &vec2);

QVector<double>& operator*=(QVector<double> &vec1, double factor);

QVector<double>& operator/=(QVector<double> &vec1, double divisor);

//-----------------------------------------------------------------------------------------------------------
QVector<double> operator+(const QVector<double> &vec1, const QVector<double> &vec2);

QVector<double> operator-(const QVector<double> &vec1, const QVector<double> &vec2);

double operator*(const QVector<double> &vec1, const QVector<double> &vec2);// скалярное умножение

QVector<double> operator*(const QVector<double> &vec1, double factor);

QVector<double> operator*(double factor, const QVector<double> &vec1);

QVector<double> operator/(const QVector<double> &vec1, double divisor);

#endif // OPERATORS

