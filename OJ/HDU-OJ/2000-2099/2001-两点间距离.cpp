#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    double x1, x2;
    double y1, y2;
    while (~scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2))
    {
        double d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        printf("%.2lf\n", d);
    }
}
