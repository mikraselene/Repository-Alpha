#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
struct player
{
    char name[100];
    int m;
    int s;
    int t;
    int rank;
};
bool cmp(player x, player y)
{
    if (x.t < y.t)
    {
        return 1;
    }
    else if (x.t == y.t)
    {
        if (strcmp(x.name, y.name) < 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
int main()
{
    int n;
    int k = 1;
    bool flag = 0;
    while (~scanf("%d", &n) && n)
    {
        player a[n];
        for (int i = 0; i < n; i++)
        {
            scanf("%s", a[i].name);
            scanf("%d:%d", &a[i].m, &a[i].s);
            a[i].t = 60 * a[i].m + a[i].s;
        }
        sort(a, a + n, cmp);
        if (flag)
        {
            printf("\n");
        }
        printf("Case #%d\n", k);
        a[0].rank = 1;
        printf("%s %d\n", a[0].name, a[0].rank);
        for (int i = 1; i < n; i++)
        {
            if (a[i].t == a[i - 1].t)
            {
                a[i].rank = a[i - 1].rank;
            }
            else
            {
                a[i].rank = i + 1;
            }
            printf("%s %d\n", a[i].name, a[i].rank);
        }
        flag = 1;
        k++;
    }
}
