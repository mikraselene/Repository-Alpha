#include <iostream>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        double x[3], y[3];
        for (int i = 0; i < 3; i++)
        {
            scanf("%lf%lf", &x[i], &y[i]);
        }
        double a;
        a = ((y[2] - y[0]) * (x[2] - x[0]) - (y[1] - y[0]) * (x[1] - x[0]));
        double b;
        b = (y[0] - (y[1] + y[2]) / 2.0) * (x[2] - x[1]);
        double area = a / 3.0 + b;
        printf("%.2lf\n", area);
    }
}
