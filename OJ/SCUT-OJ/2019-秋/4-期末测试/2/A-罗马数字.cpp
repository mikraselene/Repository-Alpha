#include <iostream>
using namespace std;
int main()
{
    int n;
    while (cin >> n)
    {
        int a = n / 1000;
        for (int i = 1; i <= a; i++)
        {
            cout << "M";
        }
        n = n % 1000;
        a = n / 100;
        if (a == 4)
        {
            cout << "CD";
        }
        else if (a == 9)
        {
            cout << "CM";
        }
        else
        {
            for (int i = 1; i <= a; i++)
            {
                cout << "C";
            }
        }
        n = n % 100;
        a = n / 10;
        if (a == 4)
        {
            cout << "LX";
        }
        else if (a == 9)
        {
            cout << "XC";
        }
        else
        {
            for (int i = 1; i <= a; i++)
            {
                cout << "X";
            }
        }
        n = n % 10;
        a = n;
        if (a == 4)
        {
            cout << "IV";
        }
        else if (a == 9)
        {
            cout << "IX";
        }
        else
        {
            for (int i = 1; i <= a; i++)
            {
                cout << "I";
            }
        }
        cout << endl;
    }
}
