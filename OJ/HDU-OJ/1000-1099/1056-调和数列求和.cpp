#include <iostream>
using namespace std;
int main()
{
    double n;
    while (~scanf("%lf", &n) && n != 0)
    {
        double sum = 0;
        int i;
        for (i = 2; i <= 300; i++)
        {
            sum += 1.0 / i;
            if (sum >= n)
                break;
        }
        printf("%d card(s)\n", i - 1);
    }
}
