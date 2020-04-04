#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int x, y;
    while (~scanf("%d%d", &x, &y))
    {
        int sqr = 0;
        int cub = 0;
        if (x > y)
        {
            swap(x, y);
        }
        for (int i = x; i <= y; i++)
        {
            if (i & 1)
            {
                cub += pow(i, 3);
            }
            else
            {
                sqr += pow(i, 2);
            }
        }
        printf("%d %d\n", sqr, cub);
    }
}
