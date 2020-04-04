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
        int x = pow(2, n) - 1;
        printf("%d\n", x);
    }
}
