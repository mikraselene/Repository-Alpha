#include <iostream>
using namespace std;
int main()
{
    char c;
    int n;
    bool flag = 0;
    while (~scanf("%c", &c) && c != '@')
    {
        if (flag)
        {
            printf("\n");
        }
        flag = 1;
        scanf("%d", &n);
        getchar();
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j <= n + i - 1; j++)
            {
                if (j == (n + i - 1) || j == (n - i + 1))
                {
                    printf("%c", c);
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        for (int i = 1; i < 2 * n; i++)
        {
            printf("%c", c);
        }
        printf("\n");
    }
}
