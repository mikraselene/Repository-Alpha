#include <cmath>
#include <iostream>
using namespace std;
bool is_prime(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int p;
        int cnt = 0;
        while (n--)
        {
            scanf("%d", &p);
            if (is_prime(p))
            {
                cnt++;
            }
        }
        printf("%d\n", cnt);
    }
}
