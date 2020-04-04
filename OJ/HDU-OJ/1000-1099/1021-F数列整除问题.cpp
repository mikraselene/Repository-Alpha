#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        if ((n - 2) % 4)
            printf("no\n");
        else
            printf("yes\n");
    }
}
