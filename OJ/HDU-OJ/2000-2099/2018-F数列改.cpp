#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        int a[60];
        a[0] = 1;
        a[1] = 1;
        a[2] = 2;
        a[3] = 3;
        for (int i = 4; i <= n; i++)
        {
            a[i] = a[i - 2] + a[i - 3] + a[i - 4];
        }
        printf("%d\n", a[n]);
    }
}
