#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    int m;
    scanf("%d", &m);
    getchar();
    while (m--)
    {
        char a[100];
        cin.getline(a, 100);
        int l = strlen(a);
        bool flag[5] = {0};
        if (l >= 8 && l <= 16)
        {
            for (int i = 0; i <= l; i++)
            {
                if (a[i] >= 'A' && a[i] <= 'Z')
                {
                    flag[1] = 1;
                }
                if (a[i] >= 'a' && a[i] <= 'z')
                {
                    flag[2] = 1;
                }
                if (a[i] >= '0' && a[i] <= '9')
                {
                    flag[3] = 1;
                }
                if (a[i] == '~' || a[i] == '!' || a[i] == '@' || a[i] == '#' || a[i] == '$' || a[i] == '%' ||
                    a[i] == '^')
                {
                    flag[4] = 1;
                }
                if (flag[1] + flag[2] + flag[3] + flag[4] >= 3)
                {
                    flag[0] = 1;
                    break;
                }
            }
        }
        if (flag[0])
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
}
