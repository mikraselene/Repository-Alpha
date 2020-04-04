#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
#define N 10
int BinarySearch(int key, int list[N])
{
    int lo = 0;
    int hi = N - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (key < list[mid])
        {
            hi = mid - 1;
        }
        else if (key > list[mid])
        {
            lo = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
int main()
{
    int list[N];
    printf("Please input %d list number(s):\n", N);
    for (int i = 0; i <= N - 1; i++)
    {
        scanf("%d", &list[i]);
    }
    sort(list, list + N);
    int key;
    printf("Please input key(s) to find out if it exists in the list:\n");
    while (scanf("%d", &key))
    {
        if (BinarySearch(key, list) >= 0)
        {
            printf("%d exists\n", key);
        }
        else
        {
            printf("%d does not exist\n", key);
        }
    }
}
