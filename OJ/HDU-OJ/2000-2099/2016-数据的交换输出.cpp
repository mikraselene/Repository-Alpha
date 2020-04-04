#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        int *a = new int[n];
        scanf("%d", &a[0]);
        int min = a[0];
        int k = 0;
        for (int i = 1; i < n; i++)
        {
            scanf("%d", &a[i]);
            if (a[i] < min)
            {
                min = a[i];
                k = i;
            }
        }
        swap(a[0], a[k]);
        printf("%d", a[0]);
        for (int i = 1; i < n; i++)
        {
            printf(" %d", a[i]);
        }
        printf("\n");
    }
}
