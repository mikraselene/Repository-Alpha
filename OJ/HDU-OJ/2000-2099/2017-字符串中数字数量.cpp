#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        char c[1000];
        scanf("%s", c);
        char *i = c;
        int cnt = 0;
        while (*i != '\0')
        {
            if (*i >= '0' && *i <= '9')
            {
                cnt++;
            }
            i++;
        }
        printf("%d\n", cnt);
    }
}
