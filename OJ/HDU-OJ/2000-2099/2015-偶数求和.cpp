#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        int *a = new int[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = 2 * i + 2;
        }
        double sum = 0;
        for (int j = 0; j < m; j++)
        {
            sum += a[j];
        }
        if (n >= m)
        {
            printf("%g", sum / m);
        }
        else
        {
            printf("%g", sum / n);
        }
        for (int i = m; i < n; i += m)
        {
            sum = 0;
            if ((n - i) >= m)
            {
                for (int j = i; j < i + m; j++)
                {
                    sum += a[j];
                }
                printf(" %g", sum / m);
            }
            else
            {
                for (int j = i; j < n; j++)
                {
                    sum += a[j];
                }
                printf(" %g", sum / (n - i));
            }
        }
        printf("\n");
    }
}
