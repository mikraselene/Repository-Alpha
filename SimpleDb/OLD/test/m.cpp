#include <unistd.h>
#include <iostream>

int main()
{
    std::cout << "\n正在输出记录数据...... ";
    for (int i = 0; i <= 1000; i++) // 打印百分比
    {
        std::cout.width(3); //i的输出为3位宽
        std::cout << i << "%";
        std::cout << "\b\b\b\b"; //回删三个字符，使数字在原地变化
    }
    std::cout << "\n\n";

    return 0;
}
