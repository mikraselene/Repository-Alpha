#include <iostream>
using namespace std;
void func(double x, double y, double z, double &p1, double &p2)
{
    double u, v;
    if (x > y)
    {
        u = x;
        v = y;
    }
    else
    {
        u = y;
        v = x;
    }
    if (z > u)
    {
        u = z;
    }

    if (z < v)
    {
        v = z;
    }
    p1 = u;
    p2 = v;
}
int main()
{
    double a, b, c, max, min;
    while (cin >> a >> b >> c)
    {
        func(a, b, c, max, min);
        cout << "max=" << max << " ";
        cout << "min=" << min << endl;
    }
}
