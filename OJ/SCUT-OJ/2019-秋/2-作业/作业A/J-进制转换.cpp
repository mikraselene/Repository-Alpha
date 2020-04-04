// 求解十进制数对应的二进制数、八进制数、十六进制数
#include <iostream>
using namespace std;
int main()
{

    int n, i, j = 0;
    int a[12];
    while (cin >> n)
    {
        i = 0;
        j = 0;
        i = n;
        while (i)
        {
            a[j] = i % 2;
            i /= 2;
            j++;
        }
        cout << "binary:";
        for (i = j - 1; i >= 0; i--)
        {
            cout << a[i];
        }
        cout << ", oct:" << oct << n << ", hex:" << hex << n;
        cout << endl;
    }
}
