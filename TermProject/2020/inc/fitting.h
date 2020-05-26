#ifndef FITTING_H
#define FITTING_H

#include <vector>
#include <iostream>

using std::vector;

class LeastSquare
{
    double k, b;
    vector<double> x;
    vector<double> y;

public:
    LeastSquare(vector<double>);
    void Fitting();

    double Y(const double);
};

#endif