// B

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
    virtual double Distance()
    {
        return sqrt(x * x + y * y);
    }

protected:
    int x;
    int y;
};

class Point3D : public MyPoint
{
public:
    Point3D()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Point3D(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    int GetZ()
    {
        return z;
    }
    double Distance()
    {
        return sqrt(x * x + y * y + z * z);
    }

private:
    int z;
};

int main()
{
    int flag, x, y, z;
    MyPoint *point = nullptr;
    while (cin >> flag)
    {
        if (1 == flag)
        {
            cin >> x >> y;
            point = new MyPoint(x, y);
        }
        else if (2 == flag)
        {
            cin >> x >> y >> z;
            point = new Point3D(x, y, z);
        }
        cout << fixed << setprecision(2);
        if (point != nullptr)
        {
            cout << point->Distance() << endl;
        }
        delete point;
        point = nullptr;
    }
}