#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int m, n;
    while (~scanf("%d%d", &m, &n))
    {
        bool flag = 0;
        if (m > n)
        {
            swap(m, n);
            flag = 1;
        }
        int max = 0;
        for (int i = m; i <= n; i++)
        {
            int n = i;
            int k = 1;
            do
            {
                if (n % 2)
                    n = 3 * n + 1;
                else
                    n /= 2;
                k++;
            } while (n != 1);
            if (k > max)
                max = k;
        }
        if (flag)
            swap(m, n);
        printf("%d %d %d\n", m, n, max);
    }
}
