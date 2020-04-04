#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int m;
    scanf("%d", &m);
    while (m--)
    {
        int n;
        scanf("%d", &n);
        int len[n];
        int f[n];
        int min = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &f[i]);
            min += f[i];
        }
        for (int i = 0; i < n; i++)
        {
            len[i] = 0;
            for (int j = 0; j < n; j++)
            {
                len[i] += abs(f[j] - f[i]);
            }
            if (len[i] < min)
            {
                min = len[i];
            }
        }
        printf("%d\n", min);
    }
}
