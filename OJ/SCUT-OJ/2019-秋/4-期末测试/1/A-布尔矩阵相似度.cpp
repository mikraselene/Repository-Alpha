#include <iostream>
using namespace std;
int main()
{
    int m, n;
    while (cin >> m >> n)
    {
        int p[200][200];
        int q[200][200];
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> p[i][j];
            }
        }
        int cnt = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> q[i][j];
                if (p[i][j] == q[i][j])
                {
                    cnt++;
                }
            }
        }
        printf("%.2f\n", 100 * cnt * 1.0 / (m * n));
    }
}
