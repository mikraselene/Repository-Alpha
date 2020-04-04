#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
struct element
{
    int id;
    double sati;
};
bool cmp1(element x, element y)
{
    return (x.sati > y.sati);
}
bool cmp2(element x, element y)
{
    return (x.id > y.id);
}
int main()
{
    int n, m, k;
    while (~scanf("%d%d%d", &n, &m, &k))
    {
        element a[m];
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                double s;
                scanf("%lf", &s);
                a[j].id = j + 1;
                a[j].sati += s;
            }
        }
        sort(a, a + m, cmp1);
        sort(a, a + k, cmp2);
        printf("%d", a[0].id);
        for (int i = 1; i < k; i++)
        {
            printf(" %d", a[i].id);
        }
        printf("\n");
    }
}
