#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    double x1, y1, x2, y2, x3, y3, x4, y4;
    while (~scanf("%lf%lf", &x1, &y1))
    {
        scanf("%lf%lf%lf%lf%lf%lf", &x2, &y2, &x3, &y3, &x4, &y4);
        if (x1 > x2)
        {
            swap(x1, x2);
        }
        if (x3 > x4)
        {
            swap(x3, x4);
        }
        if (y1 > y2)
        {
            swap(y1, y2);
        }
        if (y3 > y4)
        {
            swap(y3, y4);
        }
        double minx = x1 > x3 ? x1 : x3;
        double maxx = x2 < x4 ? x2 : x4;
        double miny = y1 > y3 ? y1 : y3;
        double maxy = y2 < y4 ? y2 : y4;
        if (minx > maxx || miny > maxy)
            printf("0.00\n");
        else
        {
            printf("%.2lf\n", (maxx - minx) * (maxy - miny));
        }
    }
}
