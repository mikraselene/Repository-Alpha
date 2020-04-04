// 感想：HDU不把题目按难度排序属实弟中弟
#include <cmath>
#include <iostream>
using namespace std;
int func(int x)
{
    int t = x + abs(5 * x);
    return t;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n != 0)
    {
        int arr[n + 1];
        arr[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &arr[i]);
        }
        int t_sum = 5 * n;
        for (int i = 1; i <= n; i++)
        {
            t_sum += func(arr[i] - arr[i - 1]);
        }
        printf("%d\n", t_sum);
    }
}
