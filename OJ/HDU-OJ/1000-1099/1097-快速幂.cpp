#include <iostream>
using namespace std;
#define ll long long
int power(ll a, ll b)
{
    int p = 1;
    while (b)
    {
        if (b % 2)
            p = (p * a) % 10;
        a = a * a % 10;
        b /= 2;
    }
    return p % 10;
}
int main()
{
    ll a, b;
    while (~scanf("%lld%lld", &a, &b))
    {
        printf("%d\n", power(a, b));
    }
}
