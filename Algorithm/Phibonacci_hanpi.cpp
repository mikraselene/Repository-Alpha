// define Φ(k, n) = (Φ(k, n - 1) + Φ(k, n - 2)) mod k
#include <iostream>
int Phibonacci(int n, int k)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }
    else
    {
        return (Phibonacci((n - 1), k) + Phibonacci((n - 2), k)) % k;
    }
}
int main()
{
    int k, num;
    while (scanf("%d%d", &k, &num))
    {
        for (int n = 1; n <= num; n++)
        {
            printf("Φ(%d, %d) = %d\n", k, n, Phibonacci(n, k) % k);
        }
    }
    return 0;
}
