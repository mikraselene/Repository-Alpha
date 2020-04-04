#include <cmath>
#include <iostream>
using namespace std;
bool is_prime(int n)
{
    if (n == 1)
    {
        return 0;
    }
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (!(n % i))
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int a;
    while (~scanf("%d", &a) && a)
    {
        int cnt = 0;
        for (int i = 1; i < a / 2; i++)
        {
            if (is_prime(i) && is_prime(a - i))
            {
                cnt++;
            }
        }
        printf("%d\n", cnt);
    }
}
