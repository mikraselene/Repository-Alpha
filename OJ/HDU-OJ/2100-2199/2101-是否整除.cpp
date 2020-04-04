#include <iostream>
using namespace std;
int main()
{
    long long m, n;
    while (~scanf("%lld%lld", &m, &n))
    {
        if ((m + n) % 86)
        {
            printf("no\n");
        }
        else
        {
            printf("yes\n");
        }
    }
}
