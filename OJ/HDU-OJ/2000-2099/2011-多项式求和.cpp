#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        double sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += 1.0 * pow(-1, i + 1) / i;
        }
        printf("%.2lf\n", sum);
    }
}
