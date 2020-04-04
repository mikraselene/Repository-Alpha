#include <iostream>
using namespace std;
int main()
{
    int a, sum;
    while (cin >> a)
    {
        sum = 0;
        for (int i = 1; i <= a; i++)
        {
            sum = sum + i;
        }
        cout << sum << endl
             << endl;
    }
}
