#include <iostream>
using namespace std;
#define PI 3.14
class Circle
{
public:
    double Area() const;
    double Volume() const;
    void Print() const;

protected:
    double radius;
};

class Sphere : public Circle
{
public:
    Sphere(double r)
    {
        radius = r;
    }
    double Area()
    {
        return 4 * PI * radius * radius;
    }
    double Volume()
    {
        return 4 * PI * radius * radius * radius / 3;
    }
    void Print()
    {
        printf("%.3f\n%.3f\n", Area(), Volume());
    }
};

class Column : public Circle
{
public:
    Column(double r, double h)
    {
        radius = r;
        height = h;
    }
    double Area()
    {
        return 2 * PI * radius * (radius + height);
    }
    double Volume()
    {
        return PI * radius * radius * height;
    }
    void Print()
    {
        printf("%.3f\n%.3f\n", Area(), Volume());
    }

private:
    double height;
};
int main()
{
    bool flag = 0;
    while (cin >> flag)
    {
        if (flag == 0)
        {
            double r = 0;
            cin >> r;
            Sphere A(r);
            A.Print();
        }
        else
        {
            double r = 0;
            double h = 0;
            cin >> r >> h;
            Column A(r, h);
            A.Print();
        }
    }
}
