#include <iostream>
using namespace std;
#define ll long long
int main()
{
    ll n;
    ll sum[100001];
    sum[1] = 1;
    sum[2] = 3;
    for (ll i = 3; i <= 100000; i++)
    {
        if (!(i % 3))
        {
            sum[i] = sum[i - 1] + i * i * i;
            // 不建议 pow(i, 3);
        }
        else
        {
            sum[i] = sum[i - 1] + i;
        }
    }
    while (~scanf("%lld", &n) && n >= 0)
    {
        printf("%lld\n", sum[n]);
    }
}
