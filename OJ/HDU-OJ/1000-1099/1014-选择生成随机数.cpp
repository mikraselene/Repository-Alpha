#include <algorithm>
#include <iostream>
using namespace std;
int gcd(int p, int q)
{
    return q ? gcd(q, p % q) : p;
}
int main()
{
    int step, mod;
    while (~scanf("%d%d", &step, &mod))
    {
        printf("%10d%10d", step, mod);
        if (gcd(step, mod) == 1)
        {
            printf("    Good Choice\n\n");
        }
        else
        {
            printf("    Bad Choice\n\n");
        }
    }
}
