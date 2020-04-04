#include <iostream>
using namespace std;
int gcd(int p, int q)
{
    return q ? gcd(q, p % q) : p;
}
int main()
{
    int n, m;
    int N;
    scanf("%d", &N);
    for (int k = 1; k <= N; k++)
    {
        int ca = 1;
        while (~scanf("%d%d", &n, &m) && (n || m))
        {
            int flag = 0;
            for (int i = 1; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if (gcd((i * i + j * j + m), i * j) == i * j)
                        flag++;
                }
            }
            printf("Case %d: %d\n", ca, flag);
            ca++;
        }
        if (k != N)
            printf("\n");
    }
}
