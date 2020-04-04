#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
bool alpha(double a, double b, double c)
{
    return (a + b) > c;
}
bool beta(double a, double b, double c)
{
    return fabs(a - b) < c;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        double x, y, z;
        scanf("%lf%lf%lf", &x, &y, &z);
        if (alpha(x, y, z) && beta(x, y, z))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
}
