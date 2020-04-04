#include <iostream>
using namespace std;
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}
int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int g = 1;
        for (int i = 1; i <= n; i++)
        {
            int m;
            scanf("%d", &m);
            g = lcm(m, g);
        }
        printf("%d\n", g);
    }
}
