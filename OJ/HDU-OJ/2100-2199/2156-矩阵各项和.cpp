#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        double sum = n;
        for (int i = 1; i < n; i++)
        {
            sum += i * 2.0 / (n - i + 1);
        }
        printf("%.2lf\n", sum);
    }
}
