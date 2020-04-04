#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int m, n;
    while (~scanf("%d%d", &m, &n))
    {
        int max = 0;
        int x = 1;
        int y = 1;
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int p;
                scanf("%d", &p);
                if (abs(p) > abs(max))
                {
                    max = p;
                    x = i;
                    y = j;
                }
            }
        }
        printf("%d %d %d\n", x, y, max);
    }
}
