#include <iostream>
using namespace std;
class Point
{
public:
    Point(double a, double b)
    {
        x = a;
        y = b;
    }
    void Print()
    {
        printf("%.2lf %.2lf\n", x, y);
    }

private:
    double x;
    double y;
};
class Line
{
public:
    Line(double x, double y)
    {
        a = x;
        b = y;
    }
    void Print()
    {
        printf("y=%lfx+%lf\n", a, b);
    }

private:
    double a;
    double b;
};

int main()
{

    double a1 = 0;
    double a2 = 0;
    double b1 = 0;
    double b2 = 0;
    while (cin >> a1 >> b1 >> a2 >> b2)
    {
        Line alpha(a1, b1);
        Line beta(a2, b2);
        double x = (b2 - b1) / (a1 - a2);
        double y = a1 * x + b1;
        Point P(x, y);
        P.Print();
    }
}