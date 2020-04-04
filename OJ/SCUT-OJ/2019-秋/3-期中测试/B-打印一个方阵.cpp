#include <iostream>
using namespace std;
int main()
{
    int m;
    while (cin >> m)
    {
        char element[12] = {' ', 'O', 'J', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char square[12][12];

        int n = (m + m % 2) / 2;
        for (int k = 1; k <= n; k++)
        {
            for (int i = k; i <= n; i++)
            {
                for (int j = k; j <= n; j++)
                {
                    square[i][j] = element[k];
                }
            }
        }

        if (m % 2 == 0)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    cout << square[i][j];
                }
                for (int j = n; j >= 1; j--)
                {
                    cout << square[i][j];
                }
                cout << endl;
            }
            for (int i = n; i >= 1; i--)
            {
                for (int j = 1; j <= n; j++)
                {
                    cout << square[i][j];
                }
                for (int j = n; j >= 1; j--)
                {
                    cout << square[i][j];
                }
                cout << endl;
            }
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    cout << square[i][j];
                }
                for (int j = n - 1; j >= 1; j--)
                {
                    cout << square[i][j];
                }
                cout << endl;
            }
            for (int i = n - 1; i >= 1; i--)
            {
                for (int j = 1; j <= n - 1; j++)
                {
                    cout << square[i][j];
                }
                for (int j = n; j >= 1; j--)
                {
                    cout << square[i][j];
                }
                cout << endl;
            }
        }
    }
}
