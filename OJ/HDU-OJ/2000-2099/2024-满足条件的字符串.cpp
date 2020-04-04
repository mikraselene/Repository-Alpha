#include <cctype>
#include <iostream>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    while (n--)
    {
        string s;
        getline(cin, s);
        bool flag = 1;
        if (isalpha(s[0]) || (s[0] == '_'))
        {
            for (int i = 1; s[i] != '\0'; i++)
            {
                if ((!isalnum(s[i])) && (s[i] != '_'))
                {
                    flag = 0;
                    break;
                }
            }
        }
        else
        {
            flag = 0;
        }
        if (flag)
        {
            printf("yes\n");
        }
        else
        {
            printf("no\n");
        }
    }
}
