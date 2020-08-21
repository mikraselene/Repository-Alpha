#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int n;
    while (cin >> n)
    {
        int i = 0;
        int cc = 0;
        for (i = 0;; i++)
        {
            if ((1 + i) * i / 2 > n)
            {
                cc = n - (i - 1) * i / 2;
                break;
            }
        }
        int sum = 0;
        int j = 0;
        for (j = 1; j < i; j++)
        {
            sum += j * j;
        }
        sum += cc * j;
        cout << sum << endl;
    }
}