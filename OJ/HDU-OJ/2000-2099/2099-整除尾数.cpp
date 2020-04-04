#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int a, b;
    while (~scanf("%d%d", &a, &b) && (a || b))
    {
        bool flag = 0;
        for (int i = 0; i <= 99; i++)
        {
            if (!((a * 100 + i) % b))
            {
                if (flag)
                {
                    printf(" ");
                }
                if (i < 10)
                {
                    printf("0%d", i);
                    flag = 1;
                }
                else
                {
                    printf("%d", i);
                    flag = 1;
                }
            }
        }
        printf("\n");
    }
}
