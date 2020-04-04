// 整数的素数因子
#include <iostream>
using namespace std;
int main()
{
    int a;
    int b;
    while (cin >> a)
    {
        for (int i = 2; i <= a; i++)
        {

            while (a % i == 0)
            {
                a /= i;
                b = i;
                cout << b << ' ';
            }
        }
        cout << endl;
    }
}
