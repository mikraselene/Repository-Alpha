#include <iostream>
using namespace std;
int power(int a, int b)
{
    int t = 1;
    while (b)
    {
        if (b & 1)
        {
            t = (t * a) % 1000;
        }
        a = (a * a) % 1000;
        b >>= 1;
    }
    return t;
}
int main()
{
    int a, b;
    while (~scanf("%d%d", &a, &b) && (a || b))
    {
        printf("%d\n", power(a, b));
    }
}
