#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int product = 1;
        int k;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &k);
            if (k & 1)
            {
                product *= k;
            }
        }
        printf("%d\n", product);
    }
}
