#include <iostream>
using namespace std;
int main()
{
    int m;
    scanf("%d", &m);
    while (m--)
    {
        int x;
        scanf("%d", &x);
        int s = 3;
        for (int i = 1; i <= x; i++)
        {
            s = (s - 1) * 2;
        }
        printf("%d\n", s);
    }
}
