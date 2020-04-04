#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        int max = 0;
        while (n--)
        {
            int s;
            scanf("%d", &s);
            if (s > max)
            {
                max = s;
            }
        }
        printf("%d\n", max);
    }
}
