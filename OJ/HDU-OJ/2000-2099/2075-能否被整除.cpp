#include <iostream>
using namespace std;
#define ll long long
int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        if (a % b)
        {
            printf("NO\n");
        }
        else
        {
            printf("YES\n");
        }
    }
}
