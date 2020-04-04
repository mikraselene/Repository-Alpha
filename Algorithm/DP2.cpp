#include <iostream>
#include <algorithm>
using namespace std;

int tri[5][5] = {{7, 0, 0, 0, 0},
                 {3, 8, 0, 0, 0},
                 {8, 1, 0, 0, 0},
                 {2, 7, 4, 4, 0},
                 {4, 5, 2, 6, 5}};
int sum[5][5] = {0};

int MaxSum(int i, int j)
{
    if (sum[i][j] != 0)
    {
        return sum[i][j];
    }
    if (i == 5)
    {
        sum[i][j] = tri[i][j];
    }
    else
    {
        int x = MaxSum(i + 1, j);
        int y = MaxSum(i + 1, j + 1);
        sum[i][j] = max(x, y) + tri[i][j];
    }
    return sum[i][j];
}

int main()
{
    cout << MaxSum(0, 0) << endl;
}