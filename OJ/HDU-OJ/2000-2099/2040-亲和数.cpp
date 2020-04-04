#include <iostream>
using namespace std;
int main()
{
    int m;
    scanf("%d", &m);
    while (m--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        int sumx = 0;
        for (int i = 1; i <= x / 2; i++)
        {
            if (!(x % i))
            {
                sumx += i;
            }
        }
        int sumy = 0;
        for (int i = 1; i <= y / 2; i++)
        {
            if (!(y % i))
            {
                sumy += i;
            }
        }
        if (sumx == y && sumy == x)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
}
