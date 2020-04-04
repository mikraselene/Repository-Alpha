#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        bool flag = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!(n % i))
            {
                flag = !flag;
            }
        }
        printf("%d\n", flag);
    }
}
