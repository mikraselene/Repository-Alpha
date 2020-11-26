#include <cmath>
#include <cstdlib>
#include <cstdio>

struct Vec
{
    double x, y, z;
    Vec(double x_ = 0, double y_ = 0, double z_ = 0)
    {
        x = x_;
        y = y_;
        z = z_;
    }
};