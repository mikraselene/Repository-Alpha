#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    for (int i = 0; i < 10; i++)
    {
        double a = 4000 + i * 10 * sqrt(2);
        double b = 4000 - i * 10 * sqrt(2);
        printf("%.2f, %.2f\n", a, b);
    }
}