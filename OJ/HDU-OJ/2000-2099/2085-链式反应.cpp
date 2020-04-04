#include <cmath>
#include <iostream>
using namespace std;
#define ll long long
int main()
{
    int n;
    while (~scanf("%d", &n) && (n != -1))
    {
        ll high = 1;
        ll low = 0;
        while (n--)
        {
            ll ts = 3 * high + 2 * low;
            ll tl = high + low;
            high = ts;
            low = tl;
        }
        printf("%lld, %lld\n", high, low);
    }
}
