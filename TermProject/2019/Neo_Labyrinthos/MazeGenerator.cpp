#include "MazeGenerator.h"

#define SHOW_GENERATING_PROCESS 0

#define State(x, y) maze[x][y].state

MazeGenerator::MazeGenerator(int l, int w)
{
    length = l + !(l % 2);
    width = w + !(w % 2);
    std::vector<std::vector<MAZE>> temp(length + 1, std::vector<MAZE>(width + 1));
    maze.resize(length + 1);
    maze.assign(temp.begin(), temp.end());

    // 生成原始地图.
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            maze[i][j].x = i;
            maze[i][j].y = j;
            maze[i][j].isBolder = (i == 1 || j == 1 || i == length || j == width);
            maze[i][j].isInS = 0;
            State(i, j) = WALL;
        }
    }

    // 初始化起始点.
    State(2, 1) = GATE;
    State(2, 2) = ROAD;
    Add2List(2, 2);

    // 直到 S 为空集才停止.
    while (!listS.empty())
    {

#if SHOW_GENERATING_PROCESS
        // 打印步骤.
        PrintProcess();

#endif

        // 随机取 S 中一个节点 Q(x, y).
        srand(time(0));
        int r = rand() % listS.size();
        auto it = listS.begin();
        for (int k = 0; k < r; k++)
        {
            it++;
        }
        listS.erase(it);
        maze[it->x][it->y].isInS = 0;
        int x = it->x;
        int y = it->y;

        // 遍历 Q(x, y) 周围的节点 P(adjx, adjy) 和 R(symx, symy):
        for (int d = 0; d < 4; d++)
        {
            int adjx = x + direction[d][0];
            int adjy = y + direction[d][1];
            int symx = x - direction[d][0];
            int symy = y - direction[d][1];

            // 若 State(R) == ROAD:
            if (State(adjx, adjy) == ROAD)
            {
                // 若 State(R) == WALL, 令 State(R) == ROAD, State(Q) == ROAD, 将 R 添加到列表 S;
                if (State(symx, symy) == WALL)
                {
                    State(symx, symy) = ROAD;
                    State(x, y) = ROAD;
                    Add2List(symx, symy);
                }

                // 否则, 令 State(Q) == WALL.
                else
                {
                    State(x, y) = WALL;
                }
                break;
            }
        }
    }

    // 随机选取一个出口.
    srand(time(0));
    int s = rand() % length;
    if (State(s, width - 1) == ROAD)
    {
        State(s, width) = GATE;
        gate = s;
    }
    else
    {
        State(length - 1, width) = GATE;
        gate = length - 1;
    }

    PrintMaze();
}

// 把节点 (x, y) 添加到列表 S.
void MazeGenerator::Add2List(int x, int y)
{
    for (int d = 0; d < 4; d++)
    {
        int adjx = x + direction[d][0];
        int adjy = y + direction[d][1];
        if (!maze[adjx][adjy].isBolder && State(adjx, adjy) != ROAD)
        {
            listS.push_back(maze[adjx][adjy]);
            maze[adjx][adjy].isInS = 1;
        }
    }
}

// 打印迷宫.
void MazeGenerator::PrintMaze()
{
    system("printf \"\033c\"");
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            switch (State(i, j))
            {
            case WALL:
                std::cout << WHITE;
                break;
            case ROAD:
                std::cout << TRANSPARENT;
                break;
            case GATE:
                std::cout << RED;
                break;
            }
        }
        printf("\n");
    }
    printf("\n(%d * %d)\n", length, width);
}

// 打印步骤.
void MazeGenerator::PrintProcess()
{
    system("printf \"\033c\"");
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            if (!maze[i][j].isInS)
            {
                if (State(i, j) == WALL)
                {
                    std::cout << WHITE;
                }
                else if (State(i, j) == GATE)
                {
                    std::cout << RED;
                }
                else
                {
                    std::cout << GREEN;
                }
            }
            else
            {
                std::cout << BLUE;
            }
        }
        printf("\n");
    }
    printf("\n(%d * %d)\n", length, width);
    usleep(50000);
}
