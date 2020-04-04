// 逆序输出一个五位整数
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (cin >> n)
    {
        for (int i = 1; i <= 5; i++)
        {

            cout << n % 10;
            if (i != 5)
            {
                cout << " ";
            }
            n = (n - n % 10) / 10;
        }
        cout << endl;
    }

    return 0;
}
