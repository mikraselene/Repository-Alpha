#include <cmath>
#include <iostream>
using namespace std;
bool is_prime(int n)
{
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
    int x, y;
    while (~scanf("%d%d", &x, &y) && (x || y))
    {
        bool flag = 1;
        for (int i = x; i <= y; i++)
        {
            int n = pow(i, 2) + i + 41;
            flag = is_prime(n);
            if (!flag)
            {
                printf("Sorry\n");
                break;
            }
        }
        if (flag)
        {
            printf("OK\n");
        }
    }
}
