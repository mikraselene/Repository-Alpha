#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m) && (n || m))
    {
        bool flag = 0;
        double delta = n * n - 4 * m;
        if (delta >= 0)
        {
            double x1 = (n + sqrt(delta)) / 2;
            double x2 = (n - sqrt(delta)) / 2;
            if (x1 == (int)x1 && x2 == (int)x2)
            {
                flag = 1;
            }
        }
        if (flag)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
}
