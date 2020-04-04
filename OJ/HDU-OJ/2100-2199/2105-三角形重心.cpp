#include <iostream>
using namespace std;
int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        while (n--)
        {
            double x1, x2, x3, y1, y2, y3;
            scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);
            double x0 = (x1 + x2 + x3) / 3;
            double y0 = (y1 + y2 + y3) / 3;
            printf("%.1lf %.1lf\n", x0, y0);
        }
    }
}
