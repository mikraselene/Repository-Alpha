#include <iostream>
using namespace std;
class Shape
{
public:
    int Calculate();

protected:
    int length;
    int width;
    int height;
};
class TwoDimShape : public Shape
{
public:
    TwoDimShape(int x, int y)
    {
        length = x;
        width = y;
    }
    int Calculate()
    {
        return length * width;
    }
};
class ThreeDimShape : public Shape
{
public:
    ThreeDimShape(int x, int y, int z)
    {
        length = x;
        width = y;
        height = z;
    }
    int Calculate()
    {
        return length * width * height;
    }
};
int main()
{
    int flag = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    while (cin >> flag)
    {
        if (flag == 2)
        {
            cin >> x >> y;
            TwoDimShape A(x, y);
            cout << A.Calculate() << endl;
        }
        if (flag == 3)
        {
            cin >> x >> y >> z;
            ThreeDimShape A(x, y, z);
            cout << A.Calculate() << endl;
        }
    }
}