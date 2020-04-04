#include <iostream>
using namespace std;
void swap(int &x, int &y)
{
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}
void swap(double &x, double &y)
{
    int *xp, *yp;
    xp = (int *)(&x);
    yp = (int *)(&y);
    *xp = (*xp) ^ (*yp);
    *yp = (*xp) ^ (*yp);
    *xp = (*xp) ^ (*yp);
    xp++;
    yp++;
    *xp = (*xp) ^ (*yp);
    *yp = (*xp) ^ (*yp);
    *xp = (*xp) ^ (*yp);
}
int main()
{
    int x, y;
    double fx, fy;
    while (cin >> x >> y >> fx >> fy)
    {
        swap(x, y);
        swap(fx, fy);
        cout << x << " " << y << "\n"
             << fx << " " << fy << "\n";
    }
}
