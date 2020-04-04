#include <iostream>
using namespace std;
#define ll long long
ll digitr(ll n)
{
    ll k = n;
    ll product = 1;
    while (k > 0)
    {
        if (k & 1)
            product = (product * n) % 10;
        n = (n * n) % 10;
        k >>= 1;
    }
    return product;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        ll n;
        scanf("%lld", &n);
        printf("%lld\n", digitr(n));
    }
}
