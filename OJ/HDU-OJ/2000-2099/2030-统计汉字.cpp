// 此代码在本机上运行错误，但可以AC
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    while (n--)
    {
        int cnt = 0;
        char a;
        while ((a = getchar()) != '\n')
        {
            if (a < 0)
            {
                cnt++;
            }
        }
        printf("%d\n", cnt / 2);
    }
}
