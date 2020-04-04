#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        if (n <= 100 && n >= 90)
        {
            printf("A\n");
        }
        else if (n <= 89 && n >= 80)
        {
            printf("B\n");
        }
        else if (n <= 79 && n >= 70)
        {
            printf("C\n");
        }
        else if (n <= 69 && n >= 60)
        {
            printf("D\n");
        }
        else if (n <= 59 && n >= 0)
        {
            printf("E\n");
        }
        else
        {
            printf("Score is error!\n");
        }
    }
}
