#include "../inc/fitting.h"

LeastSquare::LeastSquare(const std::vector<double> &y)
{
    this->y = y;
    x.resize(y.size());
    for (int i = 0; i < y.size(); i++)
    {
        x[i] = i;
    }
    k = 0;
    b = 0;
}

/*---------------------------------------------------------------------------
函数: void Fitting()

目的:
    获取以往的每月账单数据, 并根据最小二乘法拟合本月可能的账单数据.
    其中:
        Sx = Σ(0, n)x[i];
        Sx2 = Σ(0, n)x^2[i];
        Sy = Σ(0, n)y[i];
        Sxy = Σ(0, n)x[i]y[i];

             nΣx[i]y[i] - Σx[i] * Σy[i]
        k = ----------------------------;
                nΣx[i]^2 - (Σx[i])^2
        
             Σx[i]^2 * Σy[i] - Σx[i] * Σx[i]y[i]
        b = -------------------------------------.
                    nΣ(x[i]^2 - (Σx[i])^2

---------------------------------------------------------------------------*/
void LeastSquare::Fitting()
{
    double Sx = 0;
    double Sx2 = 0;
    double Sy = 0;
    double Sxy = 0;
    double n = x.size();
    for (int i = 0; i < n; i++)
    {
        Sx += x[i];
        Sx2 += x[i] * x[i];
        Sy += y[i];
        Sxy += x[i] * y[i];
    }
    k = (n * Sxy - Sx * Sy) / (n * Sx2 - Sx * Sx);
    b = (Sx2 * Sy - Sx * Sxy) / (n * Sx2 - Sx * Sx);
}

double LeastSquare::Y(const double &x) const
{
    return k * x + b;
}