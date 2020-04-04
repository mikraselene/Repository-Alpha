#include <iostream>
using namespace std;
int main()
{
    char c[100];
    bool flag = 0;
    while (~scanf("%s", c))
    {
        if (flag)
        {
            printf("\n");
        }
        int sum = 0;
        for (int i = 0; c[i] != '\0'; i++)
        {
            if ((c[i] - '0') % 2 == 0)
            {
                sum += (c[i] - '0');
            }
        }
        flag = 1;
        printf("%d\n", sum);
    }
}
