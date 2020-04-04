#include <cstdio>
#include <iostream>
using namespace std;
inline bool is_number(char ch)
{
    return (ch >= '0' && ch <= '9');
}
int main()
{
    int n = 0;
    char c;
    while ((c = getchar()) != '\n')
    {
        if (is_number(c))
        {
            n++;
        }
    }
    cout << "n = " << n << endl;
    return 0;
}
