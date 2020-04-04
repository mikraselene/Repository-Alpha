#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    double n;
    while (~scanf("%lf", &n))
    {
        printf("%.2f\n", fabs(n));
    }
}
