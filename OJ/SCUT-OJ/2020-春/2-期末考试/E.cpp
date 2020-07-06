// E

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Find(string s1, string s2)
{
    int l1 = s1.size(), l2 = s2.size(), max = 0, start = 0;
    int lcs[l1 + 1][l2 + 1];
    for (int i = 0; i <= l1; ++i)
    {
        for (int j = 0; j <= l2; ++j)
        {
            lcs[i][j] = 0;
        }
    }
    for (int i = 1; i <= l1; ++i)
    {
        for (int j = 1; j <= l2; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            }
            if (lcs[i][j] > max)
            {
                max = lcs[i][j];
                start = i - max;
            }
        }
    }
    if (s1.substr(start, max) != "")
    {
        cout << s1.substr(start, max) << endl;
    }
    else
    {
        cout << "none" << endl;
    }
}

int main()
{
    string s1, s2;
    while (getline(cin, s1) && getline(cin, s2))
    {
        if (s1.size() > s2.size())
        {
            swap(s1, s2);
        }
        Find(s1, s2);
    }
    return 0;
}