#include <iostream>
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int j = 1;
        int k = 1;
        for (int i = 1; i < n; i++)
        {
            k = (j + 1) * 2;
            j = k;
        }
        printf("%d\n", k);
    }
}
