#include <iostream>
using namespace std;
#define ll long long
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        ll F[60];
        F[1] = 3;
        F[2] = 6;
        F[3] = 6;
        for (int i = 4; i <= n; i++)
        {
            F[i] = F[i - 1] + 2 * F[i - 2];
        }
        printf("%lld\n", F[n]);
    }
}
