#include <iostream>
using namespace std;

void reverse()
{
    char ch;
    cin >> ch;
    if (ch != '.')
    {
        reverse(); // 先进后出
    }
    cout << ch;
}
int main()
{
    while (1)
    {
        reverse();
        cout << endl;
    }
}
