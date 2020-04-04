#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        printf("+");
        for (int i = 1; i <= n; i++)
        {
            printf("-");
        }
        printf("+\n");
        for (int j = 1; j <= m; j++)
        {
            printf("|");
            for (int i = 1; i <= n; i++)
            {
                printf(" ");
            }
            printf("|\n");
        }
        printf("+");
        for (int i = 1; i <= n; i++)
        {
            printf("-");
        }
        printf("+\n\n");
    }
}
