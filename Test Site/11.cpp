#include <algorithm>
#include <iostream>
using namespace std;
struct score
{
    int id;
    char name[32];
    int chn;
    int mth;
    int eng;
    double total;
};
bool cmp_total(score x, score y)
{
    return x.total > y.total;
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        score a[n];
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i].id);
            scanf("%s", a[i].name);
            scanf("%d%d%d", &a[i].chn, &a[i].mth, &a[i].eng);
            a[i].total = a[i].chn * 1.006 + a[i].mth * 1.003 + a[i].eng;
        }
        sort(a, a + n, cmp_total);
        for (int i = 0; i < n; i++)
        {
            printf("%d %s %d\n", a[i].id, a[i].name, (int)a[i].total);
        }
    }
}
