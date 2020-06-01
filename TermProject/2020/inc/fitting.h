//OK
#ifndef FITTING_H
#define FITTING_H

#include <vector>
#include <iostream>

/*---------------------------------------------------------------------------
类名: LeastSquare

描述:
    实现最小二乘法对给定数据的拟合.
---------------------------------------------------------------------------*/
class LeastSquare
{
    double k, b;
    std::vector<double> x;
    std::vector<double> y;

public:
    LeastSquare(const std::vector<double> &);
    void Fitting();

    double Y(const double &) const;
};

#endif