#include <cmath>
#include <iostream>
using namespace std;
#define ll long long
ll digitl(ll n)
{
    double nlogn = n * log10(n);
    double k = nlogn - (ll)nlogn;
    double a = pow(10, k);
    return (int)a;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        ll n;
        scanf("%lld", &n);
        printf("%lld\n", digitl(n));
    }
}
