#include <iomanip>
#include <iostream>
using namespace std;
int fact(int x)
{
    if (x == 0)
        return 1;
    else
        return x * fact(x - 1);
}
int main()
{
    printf("n e\n- -----------\n");
    printf("0 1\n1 2\n2 2.5\n");
    for (int n = 3; n <= 9; n++)
    {
        double sum = 0;
        for (int i = 0; i <= n; i++)
        {
            sum += 1.0 / fact(i);
        }
        printf("%d %.9lf\n", n, sum);
    }
}
