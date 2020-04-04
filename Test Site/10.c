#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    char name[100];
    int a, b, c, d, x, y, h, i, j, k, m = 1, n, p = 0, q, x1, a1 = 1, r, q1;
    printf("请输入你的名字：\n");
    scanf("%s", name);
    while (1)
    {
        n = 0, q = 0;
        srand(time(NULL));
        printf("游戏开始！\n请输入四个不重复一位数字：\n");
        do
        {
            h = rand() % 10;
            i = rand() % 10;
            j = rand() % 10;
            k = rand() % 10;
        } while (h == i || i == j || j == k || k == h || h == j || i == k);
        printf("%d%d%d%d\n", h, i, j, k);
        while (m <= 8)
        {
            x = 0, y = 0;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            if (a <= 9 && a >= 0 && b <= 9 && b >= 0 && c <= 9 && c >= 0 && d <= 9 && d >= 0 && a != b && a != c &&
                a != d && b != c && b != d && c != d)
                ;
            else
            {
                printf("错误输入！请重新输入！\n");
                continue;
            }
            if (a == h)
                x++;
            if (b == i)
                x++;
            if (c == j)
                x++;
            if (d == k)
                x++;
            switch (x)
            {
            case 4:
            {
                printf("哈，猜对了，你真棒！");
                m = 9, p = p + 1;
                break;
            }
            case 3:
            case 2:
            case 1:
            case 0:
                if (a == i)
                    y++;
                if (a == j)
                    y++;
                if (a == k)
                    y++;
                if (b == k)
                    y++;
                if (b == h)
                    y++;
                if (b == j)
                    y++;
                if (c == h)
                    y++;
                if (c == i)
                    y++;
                if (c == k)
                    y++;
                if (d == h)
                    y++;
                if (d == i)
                    y++;
                if (d == j)
                    y++;
                m = m + 1;
            }
            printf("%dA%dB\n", x, y);
            n = n + 1;
        }
        printf("游戏结束！\n正确的答案是：%d%d%d%d\n", h, i, j, k);

        if (q == 8)
            q1 = q1 + 1;
        printf("还想再玩一局吗？\n1.玩\t2.不玩\n");
        scanf("%d", &x1);
        switch (x1)
        {
        case 1:
        {
            m = 1, a1++;
            continue;
        }
        case 2:
            r = 100;
            break;
        }
        if (r == 100)
        {
            break;
        }
    }
    printf("%s,你玩了%d局猜数字游戏，%d赢%d负", name, a1, a1 - q1, q1);
}
