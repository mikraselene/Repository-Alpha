#include <iostream>
using namespace std;
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int m;
        scanf("%d", &m);
        int a;
        int b = 1;
        int max;
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a);
            max = a / gcd(a, b) * b;
            b = max;
        }
        printf("%d\n", b);
    }
}
