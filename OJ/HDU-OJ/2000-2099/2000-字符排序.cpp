#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    char a[3];
    while (~scanf("%s", a))
    {
        sort(a, a + 3);
        printf("%c %c %c\n", a[0], a[1], a[2]);
    }
}
