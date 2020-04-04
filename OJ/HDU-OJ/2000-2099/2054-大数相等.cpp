#include <cstring>
#include <iostream>
using namespace std;
char x[120000], y[120000];
void func(char s[])
{
    int l = strlen(s);
    bool flag = 0;
    for (int i = 0; i < l; i++)
    {
        if (s[i] == '.')
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        for (int i = l - 1; i >= 0; i--)
        {
            if (s[i] == '0')
            {
                s[i] = '\0';
            }
            else
            {
                break;
            }
            l--;
        }
        if (s[l - 1] == '.')
        {
            s[l - 1] = '\0';
            l--;
        }
    }
}
int main()
{
    while (~scanf("%s%s", x, y))
    {
        func(x);
        func(y);
        if (strcmp(x, y))
        {
            printf("NO\n");
        }
        else
        {
            printf("YES\n");
        }
    }
}
