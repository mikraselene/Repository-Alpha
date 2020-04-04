#include <iostream>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        long long k;
        scanf("%lld", &k);
        printf("%lld\n", 600000 + k % 100000);
    }
}
