#include "PathFinder.h"

#define SHOW_FINDING_PROCESS 0
#define SHOW_PATH_DIRECTLY 1

// F(P) = G(P) + H(P)
#define G1(P) (P).cost
#define G2(x, y) maze[x][y].cost
#define GetG(_1, _2, NAME, ...) NAME
#define G(...) GetG(__VA_ARGS__, G2, G1, ...)(__VA_ARGS__)
#define H(x, y) maze[x][y].estimation
#define F1(P) (P).priority
#define F2(x, y) maze[x][y].priority
#define GetF(_1, _2, NAME, ...) NAME
#define F(...) GetF(__VA_ARGS__, F2, F1, ...)(__VA_ARGS__)
#define State(x, y) maze[x][y].state

PathFinder::PathFinder(MazeGenerator m)
{
    length = m.length;
    width = m.width;
    gate = m.gate;
    std::vector<std::vector<MAZE>> temp(length + 1, std::vector<MAZE>(width + 1));
    maze.resize(length + 1);
    maze.assign(temp.begin(), temp.end());

    // 读取迷宫信息
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            maze[i][j].isRoad = (m.maze[i][j].state != MazeGenerator::WALL);
        }
    }
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            maze[i][j].x = i;
            maze[i][j].y = j;
            State(i, j) = UNDEFINED;
        }
    }

    // 初始化起始地块(2, 2)
    RemoveFromOpen(2, 2);
    G(2, 2) = 0;
    State(2, 2) = CLOSED;

    // 从地块(2, 2)开始寻路
    Find(2, 2);

    // 逆序遍历
    MAZE *ip = (MAZE *)&maze[gate][width - 1];
    while (ip->parent)
    {
        ip->parent->child = ip;
        ip = ip->parent;
    }

    // 正序遍历得到路径并打印
    MAZE *tp = (MAZE *)&maze[2][2];
    while (tp)
    {
        maze[tp->x][tp->y].isPath = 1;
        tp = tp->child;

#if !SHOW_PATH_DIRECTLY
        getchar();
        PrintPath();

#endif
    }

    PrintPath();
}

// 把地块 (x, y) 从列表 listOpen 中移除
void PathFinder::RemoveFromOpen(int x, int y)
{
    for (auto it = listOpen.begin(); it != listOpen.end();)
    {
        if (it->x == x && it->y == y)
        {
            it = listOpen.erase(it);
            if (it == listOpen.end())
            {
                break;
            }
        }
        else
        {
            it++;
        }
    }
    State(x, y) = CLOSED;
}

// 寻路算法主体.
void PathFinder::Find(int x, int y)
{
    // 记 State(T(x, y)) == CLOSED.
    RemoveFromOpen(x, y);

    // 遍历 T(x, y) 周围节点, 记周围节点为 S(adjx, adjy).
    for (int d = 0; d < 4; d++)
    {
        int adjx = x + direction[d][0];
        int adjy = y + direction[d][1];

        // 只有当 State(S) != CLOSED, 才进行操作:
        if (maze[adjx][adjy].isRoad && State(adjx, adjy) != CLOSED)
        {
            maze[adjx][adjy].parent = &maze[x][y];

            // 若 State(S) == UNDEFINED, 令 State(S) == OPEN, 计算 F(S);
            if (State(adjx, adjy) == UNDEFINED)
            {
                G(adjx, adjy) = G(*maze[adjx][adjy].parent) + 1; //计算子节点的代价.
                H(adjx, adjy) = HeuristicDistance(adjx, adjy, MANHATTAN);
                F(adjx, adjy) = G(adjx, adjy) + H(adjx, adjy);
                listOpen.push_back(maze[adjx][adjy]);
                State(adjx, adjy) = OPEN;
            }

            // 若 State(S) == OPEN, 则计算新的 F'(S). 若 F(S) > F'(S), 令 F(S) == F'(S).
            else if (State(adjx, adjy) == OPEN)
            {
                if (F(adjx, adjy) > G(adjx, adjy) + H(adjx, adjy))
                {
                    F(adjx, adjy) = G(adjx, adjy) + H(adjx, adjy);
                }
            }
        }
    }
    // 取 F 值最小的节点.
    listOpen.sort([](MAZE a, MAZE b) { return F(a) < F(b); });
    int tx = listOpen.front().x;
    int ty = listOpen.front().y;

    // 当 T 为出口才停止寻路.
    if ((x != gate) || (y != width))
    {

#if SHOW_FINDING_PROCESS
        // 打印步骤.
        PrintProcess();

#endif

        Find(tx, ty);
    }
}

// 启发式搜索距离函数.
int PathFinder::HeuristicDistance(int x, int y, int type)
{
    switch (type)
    {
    // 曼哈顿距离:
    case MANHATTAN:
        return abs(x - gate) + abs(y - width);

    // 切比雪夫距离:
    case CHEBYSHEV:
        return std::max(abs(x - gate), abs(y - width));

    // 欧几里得距离:
    case EUCLIDEAN:
        return sqrt((x - gate) * (x - gate) + (y - width) * (y - width));

    // 不使用启发式搜索:
    default:
        return 0;
    }
}

// 打印路径.
void PathFinder::PrintPath()
{
    system("printf \"\033c\"");
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            if (maze[i][j].isRoad)
            {
                if (maze[i][j].isPath)
                {
                    std::cout << GREEN;
                }
                else if ((i == 2 && j == 1) || (i == gate && j == width))
                {
                    std::cout << RED;
                }
                else
                {
                    std::cout << TRANSPARENT;
                }
            }
            else
            {
                std::cout << WHITE;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    usleep(50000);
}

// 打印步骤.
void PathFinder::PrintProcess()
{
    system("printf \"\033c\"");
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            if (maze[i][j].isRoad)
            {
                if ((i == 2 && j == 1) || (i == gate && j == width))
                {
                    std::cout << RED;
                }
                else
                {
                    switch (State(i, j))
                    {
                    case OPEN:
                        listOpen.sort([](MAZE a, MAZE b) { return F(a) < F(b); });
                        if (F(i, j) == F(listOpen.front().x, listOpen.front().y))
                        {
                            // 绿色
                            std::cout << "\033[42m"
                                      << std::setw(2) << std::setfill('0') << F(i, j) % 100
                                      << "\033[0m";
                        }
                        else
                        {
                            // 黄色
                            std::cout << "\033[43m"
                                      << std::setw(2) << std::setfill('0') << F(i, j) % 100
                                      << "\033[0m";
                        }

                        break;
                    case CLOSED:
                        std::cout << BLUE;
                        break;
                    case UNDEFINED:
                        std::cout << TRANSPARENT;
                        break;
                    }
                }
            }
            else
            {
                std::cout << WHITE;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "F(P)min = " << F(listOpen.front().x, listOpen.front().y) << std::endl;
    usleep(50000);
}
