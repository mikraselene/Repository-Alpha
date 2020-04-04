// S=[n(n+1)/2]^2
#include <cmath>
#include <iostream>
#define ll long long
using namespace std;
int main()
{
    ll n;
    while (~scanf("%lld", &n))
    {
        int k = pow((n * (n + 1) / 2) % 10000, 2);
        int s = k % 10000;
        printf("%04d\n", s);
    }
}
