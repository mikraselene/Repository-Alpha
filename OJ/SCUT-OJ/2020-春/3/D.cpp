#include <iostream>
const double PI = 3.14;
using namespace std;
class Circle
{
public:
    Circle(double radius = 0)
    {
        this->radius = radius;
    }

protected:
    double radius;
    double area;
};
class Table
{
public:
    Table(double height = 0)
    {
        this->height = height;
    }

protected:
    double height;
};
class RoundTable : public Circle, public Table
{
public:
    RoundTable(double radius, double height, string color)
    {
        this->radius = radius;
        this->height = height;
        this->color = color;
    }
    double Func()
    {
        return PI * radius * radius;
    }

private:
    string color;
};

int main()
{

    double radius = 0;
    double height = 0;
    string color = "";
    cout << "please input the data of round table:" << endl;
    cout << "radius:";
    while (cin >> radius)
    {
        cout << "height:";
        cin >> height;
        cout << "color:";
        cin >> color;
        RoundTable A(radius, height, color);
        cout << "height:" << height << endl;
        printf("area:%.2lf\n", A.Func());
        cout << "color:" << color << endl;
    }
}