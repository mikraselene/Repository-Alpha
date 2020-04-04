#include <iostream>
using namespace std;
struct point
{
    int x;
    int y;
};
//(x1*y2-x1*y3+x2*y3-x2*y1+x3*y1-x2*y2)
double area(point a, point b, point c)
{
    double s;
    s = a.x * b.y + b.x * c.y + c.x * a.y - a.x * c.y - b.x * a.y - c.x * b.y;
    return s / 2.0;
}
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        point *p = new point[n];
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &p[i].x, &p[i].y);
        }
        double s = 0;
        for (int i = 1; i < n - 1; i++)
        {
            s += area(p[0], p[i], p[i + 1]);
        }
        printf("%.1lf\n", s);
    }
}
