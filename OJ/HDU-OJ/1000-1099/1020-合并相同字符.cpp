#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        char list[10001];
        scanf("%s", list);
        int count = 1;
        for (int j = 1; j <= (int)strlen(list); j++)
        {
            if (list[j - 1] == list[j])
            {
                count++;
            }
            else
            {
                if (count != 1)
                    printf("%d%c", count, list[j - 1]);
                else
                    printf("%c", list[j - 1]);
                count = 1;
            }
        }
        printf("\n");
    }
}
