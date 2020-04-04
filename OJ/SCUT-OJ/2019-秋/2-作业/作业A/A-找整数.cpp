// 找出区间内能被3除余2，5除余3，7除余2的整数
#include <iostream>
using namespace std;
int main()
{
    int m, n, i;
    while (cin >> m >> n)
    {
        for (i = m; i <= n; i++)
        {
            if ((i % 3 == 2) && (i % 5 == 3) && (i % 7 == 2))
            {
                cout << i << endl;
            }
        }
    }
}
