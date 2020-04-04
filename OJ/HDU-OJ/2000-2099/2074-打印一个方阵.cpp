#include <iostream>
using namespace std;
#define ll long long
int main()
{
    int n;
    char a, b;
    bool flag = 0;
    while (cin >> n >> a >> b)
    {
        char map[n][n];
        for (int i = 0; i <= n / 2; i++)
        {
            for (int j = i; j < n - i; j++)
            {
                char c = a;
                if ((n / 2 - i) % 2)
                {
                    c = b;
                }
                map[i][j] = c;
                map[n - i - 1][j] = c;
                map[j][i] = c;
                map[j][n - i - 1] = c;
            }
        }
        if (flag)
        {
            printf("\n");
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if ((i && (i - n + 1)) || (j && (j - n + 1)) || n == 1)
                {
                    printf("%c", map[i][j]);
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        flag = 1;
    }
}
