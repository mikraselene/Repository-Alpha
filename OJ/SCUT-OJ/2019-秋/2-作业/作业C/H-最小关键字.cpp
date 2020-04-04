#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (cin >> n)
    {
        char string[32];
        char str[n][32];
        for (int i = 0; i < n; i++)
        {
            cin >> str[i];
        }
        strcpy(string, str[0]);
        for (int i = 0; i < n; i++)
        {
            if (strcmp(str[i], string) < 0)
                strcpy(string, str[i]);
        }
        cout << string << endl;
    }
}
