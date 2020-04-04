#include <iostream>
using namespace std;
int main()
{
    int m;
    scanf("%d", &m);
    while (m--)
    {
        int x;
        scanf("%d", &x);
        int a[50];
        a[1] = 1;
        a[2] = 1;
        for (int i = 3; i <= x; i++)
        {
            a[i] = a[i - 1] + a[i - 2];
        }
        printf("%d\n", a[x]);
    }
}
