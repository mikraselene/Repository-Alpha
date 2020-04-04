#include <iostream>
using namespace std;

void sort(double a, double b);
void sort(double x, double y, double z);
int main()
{
    double a, b, c;
    while (cin >> a >> b)
    {
        if (getchar() == '\n')
        {
            sort(a, b);
        }
        else
        {
            cin >> c;
            sort(a, b, c);
        }
    }
}
void sort(double a, double b)
{
    if (a > b)
        cout << a << " " << b << endl;
    else
        cout << b << " " << a << endl;
}
void sort(double x, double y, double z)
{
    double t;
    if (y < z)
    {
        t = y;
        y = z;
        z = t;
    }
    if (x < z)
    {
        t = x;
        x = z;
        z = t;
    }
    if (x < y)
    {
        t = x;
        x = y;
        y = t;
    }
    cout << x << " " << y << " " << z << endl;
}
