#include <stdio.h>
int func(long n)
{
    if (n >= 10)
    {
        return n % 10 + func(n / 100) * 10;
    }
    else
    {
        return n;
    }
}
int main()
{
    long n;
    scanf("%ld", &n);
    int sn = func(10 * n);
    int rn = 0;
    int temp;
    while (sn > 0)
    {
        temp = sn % 10;
        sn = sn / 10;
        rn = rn * 10 + temp;
    }
    printf("%d", rn);
}
