#include <iostream>
using namespace std;
int main()
{
    int m, n;
    while (~scanf("%d%d", &n, &m) && (n && m))
    {
        double score[100][10] = {0};
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                scanf("%lf", &score[i][j]);
                score[0][j] += score[i][j];
                score[i][0] += score[i][j];
                // 疑问：为什么把m和n在这里除了就会WA？
            }
        }
        for (int i = 1; i <= n; i++)
        {
            score[i][0] /= m;
        }
        for (int j = 1; j <= m; j++)
        {
            score[0][j] /= n;
        }
        int s = 0;
        for (int i = 1; i <= n; i++)
        {
            bool flag = 1;
            for (int j = 1; j <= m; j++)
            {
                if (score[i][j] < score[0][j])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                s++;
            }
        }
        printf("%.2lf", score[1][0]);
        for (int k = 2; k <= n; k++)
        {
            printf(" %.2lf", score[k][0]);
        }
        printf("\n%.2lf", score[0][1]);
        for (int k = 2; k <= m; k++)
        {
            printf(" %.2lf", score[0][k]);
        }
        printf("\n%d\n\n", s);
    }
}
