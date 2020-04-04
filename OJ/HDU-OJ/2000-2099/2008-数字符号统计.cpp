#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        int pos = 0;
        int zero = 0;
        int neg = 0;
        for (int i = 1; i <= n; i++)
        {
            double k;
            scanf("%lf", &k);
            if (k > 0)
            {
                pos++;
            }
            else if (k < 0)
            {
                neg++;
            }
            else
            {
                zero++;
            }
        }
        printf("%d %d %d\n", neg, zero, pos);
    }
}
