#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int *a = new int[n];
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }
        sort(a, a + n);
        double s = 0;
        for (int i = 1; i < n - 1; i++)
        {
            s += (double)a[i];
        }
        printf("%.2lf\n", s / (double)(n - 2));
    }
}
