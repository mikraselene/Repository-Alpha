#include <cmath>
#include <iostream>
using namespace std;
int dec2r(int n, int r)
{
    int sum = 0;
    while (n)
    {
        int t = n % r;
        sum += t;
        n /= r;
    }
    return sum;
}
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        int a = dec2r(n, 10);
        int b = dec2r(n, 12);
        int c = dec2r(n, 16);
        if ((a == b) && (b == c))
        {
            printf("%d is a Sky Number.\n", n);
        }
        else
        {
            printf("%d is not a Sky Number.\n", n);
        }
    }
}
