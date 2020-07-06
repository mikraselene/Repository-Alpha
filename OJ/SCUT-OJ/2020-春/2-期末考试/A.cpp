// A

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class MyPoint
{
public:
    MyPoint()
    {
        x = 0;
        y = 0;
    }
    MyPoint(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int GetX()
    {
        return x;
    }
    int GetY()
    {
        return y;
    }
    MyPoint &operator++()
    {
        x++;
        y++;
        return *this;
    }
    MyPoint operator--()
    {
        x--;
        y--;
        return *this;
    }
    double Distance()
    {
        return sqrt(x * x + y * y);
    }

private:
    int x;
    int y;
};

int main()
{
    int x, y;
    while (cin >> x >> y)
    {
        MyPoint point(x, y);
        cout << point.GetX() << " " << point.GetY() << endl;
        ++point;
        cout << fixed << setprecision(2);
        cout << point.Distance() << endl;
        --point;
        cout << point.Distance() << endl;
    }
}