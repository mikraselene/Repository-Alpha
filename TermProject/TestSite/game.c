#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    char name[100];
    printf("请输入你的名字：\n");
    int n = 0;
    int win = 0; // n场游戏中赢的次数
    scanf("%s", name);
    printf("你总共要玩几局游戏? \n");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        printf("第%d局游戏开始！\n请输入四个不重复一位数字：\n", i);
        srand(time(NULL));

        // u，v，z，w是四个随机数
        int u, v, z, w;
        do
        {
            u = rand() % 10;
            v = rand() % 10;
            z = rand() % 10;
            w = rand() % 10;
        } while (u == v || u == z || u == w || v == z || v == w || z == w);

        for (int j = 1; j <= 8; j++)
        {
            int x = 0;
            int y = 0;
            int input;          // 输入一个四位数
            int a, b, c, d;     // 这个四位数各位
            int is_illegal = 0; // 用来判断输入是否正确
            scanf("%d", &input);
            if (input < 9999 && input > 0) // 四位数必须小于四位
            {
                // 把四位数的四位分别赋值给a，b，c，d
                d = input % 10;
                input /= 10;
                c = input % 10;
                input /= 10;
                b = input % 10;
                input /= 10;
                a = input % 10;
                input /= 10;
                // 判定是否有重复，如果有，则输入错误
                if (a == b || a == c || a == d || b == c || b == d || c == d)
                {
                    is_illegal = 1;
                }
            }
            else // 其他情况也是输入错误
            {
                is_illegal = 1;
            }
            if (is_illegal == 1) // 如果输入错误则返回错误信息并要求重新输入
            {
                printf("illegal input\n");
                j--;      // j--的目的是如果输入错误，不参与8次计数
                continue; //结束这个循环
            }

            // 判断有几个“A”
            if (a == u)
                x++;
            if (b == v)
                x++;
            if (c == z)
                x++;
            if (d == w)
                x++;
            if (x == 4)
            {
                printf("哈，猜对了，你真棒！");
                win++; //赢的次数加一
                break;
            }
            else
            {
                // 判断有几个“B”
                if (a == v)
                    y++;
                if (a == z)
                    y++;
                if (a == w)
                    y++;
                if (b == u)
                    y++;
                if (b == z)
                    y++;
                if (b == w)
                    y++;
                if (c == u)
                    y++;
                if (c == v)
                    y++;
                if (c == w)
                    y++;
                if (d == u)
                    y++;
                if (d == v)
                    y++;
                if (d == z)
                    y++;
            }
            printf("%dA%dB\n", x, y); // 输出几A几B
        }
        printf("游戏结束! \n正确的答案是: %d%d%d%d\n", u, v, z,
               w); // 一场结束，公布答案
    }
    printf("%s, 你玩了%d局猜数字游戏, %d胜%d负\n", name, n, win, n - win);
}
