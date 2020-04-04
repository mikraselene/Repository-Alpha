#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int m, n, i, narc;

    while (cin >> m >> n)
    {
        int flag = 0;
        int first = 0;
        for (i = m; i <= n; i++)
        {
            narc = pow(((i % 100) % 10), 3) + pow((i % 100) / 10, 3) + pow((i / 100), 3);
            if (narc == i)
            {
                flag = 1;
                if (!first)
                {
                    cout << i;
                    first = 1;
                }
                else
                {
                    cout << " " << i;
                }
            }
        }
        if (flag == 0)
        {
            cout << "no";
        }
        cout << endl;
    }
}
