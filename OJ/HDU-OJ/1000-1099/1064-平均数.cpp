#include <iostream>
using namespace std;
int main()
{
    double a[12];
    double sum = 0;
    for (int i = 0; i < 12; i++)
    {
        scanf("%lf", &a[i]);
        sum += a[i];
    }
    printf("$%.2lf\n", sum / 12);
}
