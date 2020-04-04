#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (cin >> n)
    {
        int *x = new int[n];
        int *p = new int[n];
        for (int i = 0; i < n; i++)
        {
            cin >> x[i] >> p[i];
        }
        int m;
        cin >> m;
        int *y = new int[m + 1];
        int *z = new int[m + 1];
        for (int i = 1; i <= m; i++)
        {
            cin >> y[i] >> z[i];
        }
        double *sum = new double[m + 1];
        for (int i = 0; i < m + 1; i++)
        {
            sum[i] = 0.0;
        }
        for (int i = 0; i < n; i++)
        {
            if (p[i] == 1)
            {
                sum[0] += x[i] * 0.8;
            }
            else
            {
                sum[0] += x[i];
            }
        }
        for (int i = 1; i <= m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum[i] += x[j];
            }
            if (sum[i] >= y[i])
                sum[i] -= z[i];
        }
        sort(sum, sum + m + 1);
        printf("%.2f\n", sum[0]);
    }
}
