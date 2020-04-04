#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    while (n--)
    {
        char s[1000];
        cin.getline(s, 1000);
        int l = strlen(s);
        bool flag = 1;
        for (int i = 0; i <= l / 2; i++)
        {
            if (s[i] != s[l - i - 1])
            {
                flag = 0;
            }
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
