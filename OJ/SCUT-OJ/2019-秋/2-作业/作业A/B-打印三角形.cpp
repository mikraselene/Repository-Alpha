// 打印三角形图案
#include <iostream>
using namespace std;
int main()
{
    int n, i, j;
    char c;
    while (cin >> n >> c)
    {
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n - i; j++)
            {
                cout << " ";
            }
            for (j = 1; j <= 2 * i - 1; j++)
            {
                cout << c;
            }
            cout << endl;
        }
    }
}
