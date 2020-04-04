#include <iostream>
using namespace std;
int main()
{
    string s;
    while (getline(cin, s))
    {
        char max = 0;
        for (int i = 0; s[i] != '\0'; i++)
        {
            if (s[i] >= max)
            {
                max = s[i];
            }
        }
        for (int i = 0; s[i] != '\0'; i++)
        {
            printf("%c", s[i]);
            if (s[i] == max)
            {
                printf("(max)");
            }
        }
        printf("\n");
    }
}
