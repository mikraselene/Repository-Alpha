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
        int fa = 0;
        int fe = 0;
        int fi = 0;
        int fo = 0;
        int fu = 0;
        for (int i = 0; s[i] != '\0'; i++)
        {
            if (s[i] == 'a' || s[i] == 'A')
            {
                fa++;
            }
            if (s[i] == 'e' || s[i] == 'E')
            {
                fe++;
            }
            if (s[i] == 'i' || s[i] == 'I')
            {
                fi++;
            }
            if (s[i] == 'o' || s[i] == 'O')
            {
                fo++;
            }
            if (s[i] == 'u' || s[i] == 'U')
            {
                fu++;
            }
        }
        printf("a:%d\ne:%d\ni:%d\no:%d\nu:%d\n", fa, fe, fi, fo, fu);
        if (n)
        {
            printf("\n");
        }
    }
}
