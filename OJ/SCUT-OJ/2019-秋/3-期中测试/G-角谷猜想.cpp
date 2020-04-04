#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
int main()
{
    int n, t, flag;
    while (cin >> t)
    {
        while (t--)
        {
            cin >> n;
            flag = 1;
            while (n != 1)
            {
                if (n % 2)
                {
                    if (flag)
                    {
                        cout << n;
                        flag = 0;
                    }
                    else
                        cout << " " << n;
                    n = 3 * n + 1;
                }
                else
                    n = n / 2;
            }
            if (flag)
                cout << "No number can be output !" << endl;
            else
                cout << endl;
        }
    }
}
