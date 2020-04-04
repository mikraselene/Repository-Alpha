#include <cmath>
#include <iostream>
using namespace std;
void dec2r(int n, int r)
{
    if (n >= r)
    {
        dec2r(n / r, r);
    }
    int t = n % r;
    if (t <= 9 && t >= 0)
    {
        printf("%d", t);
    }
    else
    {
        printf("%c", 'A' + t - 10);
    }
}
int main()
{
    int n, r;
    while (~scanf("%d%d", &n, &r))
    {
        if (n < 0)
        {
            printf("-");
        }
        dec2r(abs(n), r);
        printf("\n");
    }
}
