#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int a[30], b[30];
        for (int i = 0; i <= n; i++)
        {
            a[i] = 1;
            b[i] = 1;
        }
        printf("1\n");
        for (int i = 1; i < n; i++)
        {
            printf("1 ");
            for (int j = 1; j < i; j++)
            {
                int t = a[j - 1] + a[j];
                printf("%d ", t);
                b[j] = t;
            }
            for (int k = 0; k <= i; k++)
            {
                a[k] = b[k];
            }
            printf("1\n");
        }
        printf("\n");
    }
}
