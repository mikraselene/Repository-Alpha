#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m) && (n || m))
    {
        for (int i = sqrt(2 * m); i >= 1; i--)
        {
            int a = (m - ((i - 1) * i) / 2) / i;
            if (m == a * i + (i * (i - 1)) / 2 && a > 0)
                printf("[%d,%d]\n", a, a + i - 1);
        }
        printf("\n");
    }
}
