#include <iostream>
#define ll long long
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        ll F[50];
        F[1] = 1;
        F[2] = 1;
        for (int i = 3; i <= b - a + 1; i++)
        {
            F[i] = F[i - 1] + F[i - 2];
        }
        printf("%lld\n", F[b - a + 1]);
    }
}
