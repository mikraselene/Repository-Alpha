#include <algorithm>
#include <iostream>
using namespace std;
struct student
{
    int id;
    int solved;
    int time;
    int total;
    int score;
} a[200];
bool cmp1(student a, student b)
{
    if (a.solved > b.solved)
        return true;
    if (a.solved == b.solved)
    {
        return (a.time < b.time);
    }
    return false;
}
bool cmp2(student a, student b)
{
    return (a.id < b.id);
}

int main()
{
    int n;
    int h, m, s;
    while (~scanf("%d", &n) && n > 0)
    {
        int cnt[6] = {0};
        for (int i = 0; i < n; i++)
        {
            a[i].id = i;
            scanf("%d", &a[i].solved);
            cnt[a[i].solved]++;
            scanf("%d:%d:%d", &h, &m, &s);
            a[i].time = h * 3600 + m * 60 + s;
        }
        sort(a, a + n, cmp1);
        int k = 0;
        for (int i = 5; i >= 0; i--)
        {
            if (i == 5)
            {
                for (int j = 0; j < cnt[i]; j++)
                {
                    a[k++].score = 100;
                }
            }
            else if (i == 0)
            {
                for (int j = 0; j < cnt[0]; j++)
                {
                    a[k++].score = 50;
                }
            }
            else
            {
                for (int j = 0; j < cnt[i] / 2; j++)
                {
                    if (i == 4)
                        a[k++].score = 95;
                    if (i == 3)
                        a[k++].score = 85;
                    if (i == 2)
                        a[k++].score = 75;
                    if (i == 1)
                        a[k++].score = 65;
                }
                for (int j = cnt[i] / 2; j < cnt[i]; j++)
                {
                    if (i == 4)
                        a[k++].score = 90;
                    if (i == 3)
                        a[k++].score = 80;
                    if (i == 2)
                        a[k++].score = 70;
                    if (i == 1)
                        a[k++].score = 60;
                }
            }
        }
        sort(a, a + n, cmp2);
        for (int i = 0; i < k; i++)
        {
            printf("%d\n", a[i].score);
        }
        printf("\n");
    }
}
