#include <iostream>
int GCD(int p, int q)
{
    if (q == 0)
    {
        return p;
    }
    else
    {
        return GCD(q, p % q);
    }
}
int main()
{
    int p, q;
    scanf("%d%d", &p, &q);
    printf("%d\n", GCD(p, q));
}
