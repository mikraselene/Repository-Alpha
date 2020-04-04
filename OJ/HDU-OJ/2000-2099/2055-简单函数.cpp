#include <iostream>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    getchar();
    while (t--)
    {
        char c;
        int y;
        scanf("%c %d", &c, &y);
        getchar();
        if (c >= 'A' && c <= 'Z')
        {
            printf("%d\n", c - 'A' + 1 + y);
        }
        if (c >= 'a' && c <= 'z')
        {
            printf("%d\n", -c + 'a' - 1 + y);
        }
    }
}
