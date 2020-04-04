#include <cstring>
#include <iostream>
using namespace std;
void sswap(char x[], int lx)
{
    for (int i = 0; i < lx / 2; i++)
    {
        swap(x[i], x[lx - 1 - i]);
    }
}
void addzero(char x[], int lx, int lm)
{
    for (int i = lx; i < lm; i++)
    {
        x[i] = 'A';
    }
    x[lm] = '\0';
}
int main()
{
    char a[300];
    char b[300];
    char c[300];
    memset(a, 'A', sizeof(a));
    memset(b, 'A', sizeof(b));
    memset(c, 'A', sizeof(c));
    int f = 0;
    while (~scanf("%s%s", a, b))
    {
        int la = strlen(a);
        int lb = strlen(b);
        sswap(a, la);
        sswap(b, lb);
        int lm = max(la, lb);
        if (la > lb)
        {

            addzero(b, lb, lm);
        }
        else
        {
            addzero(a, la, lm);
        }
        c[0] = a[0] + b[0] - 'A';
        for (int i = 0; i < lm; i++)
        {
            f = 0;
            if (c[i] > 'Z')
            {
                c[i] -= ('Z' - 'A' + 1);
                f = 1;
            }
            if (i + 1 < lm)
                c[i + 1] = a[i + 1] + b[i + 1] + f - 'A';
        }
        if (f)
        {
            c[lm] = 'B';
            c[lm + 1] = '\0';
        }
        else
        {
            c[lm] = '\0';
        }
        int l = strlen(c);
        sswap(c, l);
        bool flag = 0;
        for (int i = 0; c[i] != '\0'; i++)
        {
            if (c[i] != 'A')
            {
                flag = 1;
            }
            if (flag)
            {
                printf("%c", c[i]);
            }
        }
        printf("\n");
    }
}
