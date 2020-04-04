#include <iostream>
using namespace std;
int main()
{
    char n[1000];
    while (scanf("%s", n))
    {
        if (n[0] == '0')
            break;
        int sum = 0;
        for (int i = 0; n[i]; i++)
        {
            sum += n[i] - '0';
        }
        printf("%d\n", (sum - 1) % 9 + 1);
    }
    return 0;
}
