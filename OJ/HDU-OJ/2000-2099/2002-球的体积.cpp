#include <cmath>
#include <iostream>
using namespace std;
#define PI 3.1415927
int main()
{
    double r;
    while (~scanf("%lf", &r))
    {
        double v = 4 * PI * pow(r, 3) / 3;
        printf("%.3lf\n", v);
    }
}
