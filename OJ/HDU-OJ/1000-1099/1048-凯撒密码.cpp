#include <cctype>
#include <cstring>
#include <iostream>
char m[1000];
using namespace std;
int main()
{
    while (cin.getline(m, 1000))
    {
        if (!strcmp(m, "ENDOFINPUT"))
            break;
        else if (!strcmp(m, "START") || !strcmp(m, "END"))
            continue;
        for (int i = 0; m[i]; ++i)
        {
            if (isalpha(m[i]))
                m[i] = ((m[i] - 'A') + 21) % 26 + 'A';
        }
        puts(m);
    }
    return 0;
}
