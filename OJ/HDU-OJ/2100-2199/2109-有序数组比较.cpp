#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        int a[n];
        int b[n];
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &b[i]);
        }
        sort(a, a + n);
        sort(b, b + n);
        int as = 0;
        int bs = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] > b[i])
            {
                as += 2;
            }
            if (a[i] == b[i])
            {
                as++;
                bs++;
            }
            if (a[i] < b[i])
            {
                bs += 2;
            }
        }
        printf("%d vs %d\n", as, bs);
    }
}
