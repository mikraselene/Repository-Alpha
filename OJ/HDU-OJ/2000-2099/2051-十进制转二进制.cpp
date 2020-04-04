#include <cmath>
#include <iostream>
using namespace std;
void dec22(int n)
{
    if (n >= 2)
    {
        dec22(n / 2);
    }
    printf("%d", n % 2);
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        dec22(n);
        printf("\n");
    }
}
