// 打印小于等于n的所有完数
#include <iostream>
using namespace std;

int main()
{
    int sum = 0;
    int n;
    int lim;
    while (cin >> lim)
    {

        for (n = 1; n <= lim; n++)
        {
            sum = 0;
            for (int i = 1; i <= n / 2; i++)
            {
                if (n % i == 0)
                {
                    sum = sum + i;
                }
            }
            if (sum == n)
            {
                cout << sum << " ";
            }
        }
        cout << endl;
    }
}
