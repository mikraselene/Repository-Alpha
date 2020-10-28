#include <iostream>
using namespace std;
bool flag = 0;
bool password(int key)
{
    flag = 0;
    int n = 0;
    int k;
    cout << "Please input your password: \n";
    cin >> k;
    n++;
    if (n < 3)
    {
        if (key == k)
        {
            flag = 1;
        }
        else
        {
            cout << "Try again.\n";
            password(key);
        }
    }
    else
    {
        if (k != key)
        {
            flag = 0;
        }
    }
    return flag;
}
int main()
{
    if (password(114514))
    {
        cout << "Welcome!\n";
    }
    else
    {
        cout << "Access denied.\n";
    }
}
