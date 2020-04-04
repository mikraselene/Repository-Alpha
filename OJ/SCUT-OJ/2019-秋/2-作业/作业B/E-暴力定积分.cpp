#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
double func1(double x)
{
    return 4 / (1 + x * x);
}
double func2(double x)
{
    return sqrt(1 + x * x);
}
double func3(double x)
{
    return sin(x);
}
double f(double (*func)(double x), double a, double b, int n)
{
    double t, h;
    t = ((*func)(a) + (*func)(b)) / 2.0;
    h = (b - a) / n;
    for (int i = 1; i <= n - 1; i++)
    {
        t += (*func)(a + i * h);
    }
    t *= h;
    return t;
}
int main()
{
    int num, n;
    double a, b;
    while (cin >> num >> n >> a >> b)
    {

        switch (num)
        {
        case 1:
            cout << fixed << setprecision(2) << f(func1, a, b, n) << endl;
            break;
        case 2:
            cout << fixed << setprecision(2) << f(func2, a, b, n) << endl;
            break;
        case 3:
            cout << fixed << setprecision(2) << f(func3, a, b, n) << endl;
            break;
        }
    }
}
