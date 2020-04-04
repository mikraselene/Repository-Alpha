#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
double sum(double n, int m)
{
    if (m)
    {
        return n + sum(sqrt(n), m - 1);
    }
    else
    {
        return 0;
    }
}
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        printf("%.2lf\n", sum((double)n, m));
    }
}
