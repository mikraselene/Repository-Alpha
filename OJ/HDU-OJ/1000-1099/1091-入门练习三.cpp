#include <iostream>
using namespace std;
int main()
{
    int a, b;
    while (scanf("%d%d", &a, &b) && (a || b) != 0)
    {
        printf("%d\n", a + b);
    }
}
