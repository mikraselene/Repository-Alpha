// F

#include <iostream>
#include <algorithm>

using namespace std;

bool cmp(string a, string b)
{
    return a + b > b + a;
}

int main()
{
    int n;
    while (cin >> n && n != -1)
    {
        string num[n];
        for (int i = 0; i < n; i++)
        {
            cin >> num[i];
        }
        sort(num, num + n, cmp);
        for (int i = 0; i < n; i++)
        {
            cout << num[i];
        }
        cout << endl;
    }
}
