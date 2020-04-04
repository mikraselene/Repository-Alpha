#include <iostream>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int m;
        scanf("%d", &m);
        int a[m];
        int sum = 0;
        for (int i = 0; i < m; i++)
        {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        printf("%d\n", sum);
    }
}
