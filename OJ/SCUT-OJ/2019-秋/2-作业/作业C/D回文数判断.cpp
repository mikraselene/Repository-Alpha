
#include <iostream>
#include <string>
using namespace std;
inline bool hw(const string str)
{
    int length = str.length();
    for (int i = 0; i < length / 2; ++i)
        if (str[i] != str[length - i - 1])
            return false;
    return true;
};
int main()
{
    string str;
    while (cin >> str)
    {
        if (hw(str))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
};
