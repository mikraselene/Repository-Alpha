#include <iostream>
using namespace std;
#define ll long long
int main()
{
    int c;
    scanf("%d", &c);
    while (c--)
    {
        int n;
        scanf("%d", &n);
        double F[30];
        ll sum = 2;
        F[1] = 0;
        F[2] = 1;
        for (int i = 3; i <= n; i++)
        {
            sum *= i;
            F[i] = (i - 1) * (F[i - 1] + F[i - 2]);
        }
        printf("%.2lf%%\n", F[n] / sum * 100);
    }
}
