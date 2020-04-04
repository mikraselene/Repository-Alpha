#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        int sum = 0;
        int num;
        for (int i = 1; i <= n; i++)
        {
            num = 0;
            int salary;
            scanf("%d", &salary);
            num += salary / 100;
            salary %= 100;
            num += salary / 50;
            salary %= 50;
            num += salary / 10;
            salary %= 10;
            num += salary / 5;
            salary %= 5;
            num += salary / 2;
            salary %= 2;
            num += salary;
            sum += num;
        }
        printf("%d\n", sum);
    }
}
