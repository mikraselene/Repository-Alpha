#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int m;
        scanf("%d", &m);
        int list[m];
        for (int j = 0; j < m; j++)
            scanf("%d", &list[j]);
        sort(list, list + m);
        for (int j = 0; j < m - 1; j++)
            printf("%d ", list[j]);
        printf("%d\n", list[m - 1]);
    }
}
