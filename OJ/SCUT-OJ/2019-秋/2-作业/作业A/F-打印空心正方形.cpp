// 空心正方形
#include <iostream>
using namespace std;
int main()
{
    int n, i, j;
    while (cin >> n)
    {
        if (n == 1)
        {
            cout << "*\n";
        }
        else
        {
            for (i = 1; i <= n - 1; i++)
            {
                cout << "* ";
            }
            cout << "*\n";
            for (i = 1; i <= n - 2; i++)
            {
                cout << "*";
                for (j = 1; j <= 2 * n - 3; j++)
                {
                    cout << " ";
                }
                cout << "*\n";
            }
            for (i = 1; i <= n - 1; i++)
            {
                cout << "* ";
            }
            cout << "*\n";
        }
    }
}
