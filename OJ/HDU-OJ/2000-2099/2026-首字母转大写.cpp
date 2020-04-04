#include <iostream>
using namespace std;
int main()
{
    string s;
    while (getline(cin, s))
    {
        printf("%c", s[0] + 'A' - 'a');
        ;
        for (int i = 1; s[i] != '\0'; i++)
        {
            if (s[i - 1] == ' ')
            {
                s[i] += 'A' - 'a';
            }
            printf("%c", s[i]);
        }
        printf("\n");
    }
}
