#include <iostream>
using namespace std;
bool is_leap(int n)
{
    return (!(n % 4) && (n % 100)) || !(n % 400);
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int cur;
        int itv;
        scanf("%d%d", &cur, &itv);
        int cnt = 0;
        int i;
        for (i = cur;; i++)
        {
            if (is_leap(i))
                cnt++;
            if (cnt == itv)
                break;
        }
        printf("%d\n", i);
    }
}
