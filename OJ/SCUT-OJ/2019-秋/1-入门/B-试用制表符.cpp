// 用制表符整齐格式显示计算结果
#include <iostream>
using namespace std;
int main()
{
    int i;
    for (i = 0; i <= 10; i++)
    {
        printf("%d\t%d\t%d\n", i, i * i, i * i * i);
    }
}
