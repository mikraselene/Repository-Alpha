#include <cmath>
#include <iostream>
using namespace std;
double func(int n)
{
    return sqrt(n * n + (n + 1) * (n + 1));
}
double len(int x, int y)
{
    double l = sqrt(2) * (x + (x + y) * (x + y - 1) / 2);
    for (int i = 0; i < x + y; i++)
    {
        l += func(i);
    }
    return l;
}
int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        double l1 = len(x1, y1);
        double l2 = len(x2, y2);
        printf("%.3f\n", fabs(l2 - l1));
    }
}
