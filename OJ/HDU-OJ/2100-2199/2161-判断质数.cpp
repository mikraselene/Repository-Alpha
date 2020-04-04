#include <cmath>
#include <iostream>
using namespace std;
bool is_prime(int n)
{
    if (n == 1 || n == 2)
    {
        return 0;
    }
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
    int i = 1;
    while (~scanf("%d", &n) && n > 0)
    {
        printf("%d: ", i);
        i++;
        if (is_prime(n))
        {
            printf("yes\n");
        }
        else
        {
            printf("no\n");
        }
    }
}
