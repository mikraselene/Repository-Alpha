#include <iostream>
using namespace std;
#define ll long long
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        ll F[60];
        F[1] = 1;
        F[2] = 2;
        for (int i = 3; i <= n; i++)
        {
            F[i] = F[i - 1] + F[i - 2];
        }
        printf("%lld\n", F[n]);
    }
}
