/****************************************************************\

Copyright (c) 2020 Parvaluna

Author: Parvaluna, SCUT

Date: 2020-02-13

Description: Generate a maze ramdomly and find its shortest path. 

\****************************************************************/

#include <iostream>
#include <list>

using namespace std;

#define MAX_N 200
#define WALL "# "
#define GATE "->"
#define ROAD "  "
#define PATH "· "
#define M(x, y) la[x][y].maze
#define B(x, y) la[x][y].base
#define F(x, y) lb[x][y].priority
#define G(x, y) lb[x][y].cost
#define H(x, y) lb[x][y].estimation

struct MAZEBUILD
{
    int x;
    int y;
    int maze; // 1 = road, 0 = entry and exit, -1 = wall
    bool base;
    bool isBolder;
};
struct PATHFIND
{
    int x;
    int y;
    int priority;
    int cost;
    int estimation;
    int status; // 1 = open, 0 = undefined, -1 = closed
    bool isPath;
    bool isRoad;
    PATHFIND *parent;
};

MAZEBUILD la[MAX_N][MAX_N] = {};
PATHFIND lb[MAX_N][MAX_N] = {};
int length = 0;
int width = 0;
int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

#pragma region "Generate the maze"

list<MAZEBUILD> listS;

void GenerateMap()
{
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            la[i][j].x = i;
            la[i][j].y = j;
            la[i][j].isBolder =
                (i == 1 || j == 1 || i == length || j == width);
            B(i, j) = !((i % 2) || (j % 2));
            M(i, j) = -1;
        }
    }

    M(2, 1) = 0;
    M(length - 1, width) = 0;
}

// Add the adjacent landblocks of the landblock (x, y) to S.
void AddToS(int x, int y)
{
    for (int d = 0; d < 4; d++)
    {
        int adjx = x + direction[d][0];
        int adjy = y + direction[d][1];
        if (!la[adjx][adjy].isBolder && M(adjx, adjy) != 1)
        {
            listS.push_back(la[adjx][adjy]);
        }
    }
}

void PaveMaze(int x, int y, int symx, int symy)
{
    if (M(symx, symy) == -1)
    {
        M(symx, symy) = 1;
        M(x, y) = 1;
        AddToS(symx, symy);
    }
    else
    {
        M(x, y) = -1;
    }
}

// Select a landblock from S and traverse its adjacent landblocks.
void SelectFromS()
{
    srand(time(0));
    int r = rand() % listS.size();
    list<MAZEBUILD>::iterator it;
    it = listS.begin();
    for (int k = 0; k < r; k++)
    {
        it++;
    }
    listS.erase(it);

    int tx = it->x;
    int ty = it->y;
    for (int d = 0; d < 4; d++)
    {
        int adjx = tx + direction[d][0];
        int adjy = ty + direction[d][1];
        int symx = tx - direction[d][0];
        int symy = ty - direction[d][1];
        if (M(adjx, adjy) == 1 && B(adjx, adjy) == 1)
        {
            PaveMaze(tx, ty, symx, symy);
            break;
        }
    }
}

// Print the maze without the path.
void PrintMaze()
{
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            switch (M(i, j))
            {
            case -1:
                printf(WALL);
                break;
            case 0:
                printf(GATE);
                break;
            case 1:
                printf(ROAD);
                break;
            }
        }
        printf("\n");
    }
    printf("(%d * %d)\n", length, width);
}

void GenerateMaze()
{
    // The length and the width should be odd numbers.
    length += !(length % 2);
    width += !(width % 2);

    GenerateMap();
    M(2, 2) = 1;
    AddToS(2, 2);

    // Stop when S is empty.
    while (listS.size())
    {
        SelectFromS();
    }

    PrintMaze();
}

#pragma endregion

void ReadMaze()
{
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            lb[i][j].isRoad = (la[i][j].maze != -1);
        }
    }
}

#pragma region "Find the path of the maze"

list<PATHFIND> listOpen;

bool cmp(PATHFIND a, PATHFIND b)
{
    return F(a.x, a.y) < F(b.x, b.y);
}

int ManhattanD(int x, int y)
{
    return abs(x - (length - 1)) + abs(y - width);
}

// Add the landblock (x, y) to open and calculate F(x, y).
void AddToOpen(int x, int y)
{
    listOpen.push_back(lb[x][y]);
    lb[x][y].status = 1;

    G(x, y) = lb[x][y].parent->cost + 1;
    H(x, y) = ManhattanD(x, y);
    F(x, y) = H(x, y) + G(x, y);
}

// Remove the landblock (x, y) from open.
void RemoveFromOpen(int x, int y)
{
    list<PATHFIND>::iterator it;
    for (it = listOpen.begin(); it != listOpen.end(); it++)
    {
        if (it->x == x && it->y == y)
        {
            it = listOpen.erase(it);
            if (it == listOpen.end())
            {
                break;
            }
        }
    }
    lb[x][y].status = -1;
}

void JudgeStu(int x, int y)
{
    if (lb[x][y].status == 0)
    {
        AddToOpen(x, y);
    }
    else if (lb[x][y].status == 1)
    {
        if (G(x, y) + H(x, y) < F(x, y))
        {
            F(x, y) = G(x, y) + H(x, y);
        }
    }
}

void FindPath(int x, int y)
{
    RemoveFromOpen(x, y);

    for (int d = 0; d < 4; d++)
    {
        int adjx = x + direction[d][0];
        int adjy = y + direction[d][1];
        if (lb[adjx][adjy].isRoad && lb[adjx][adjy].status != -1)
        {
            lb[adjx][adjy].parent = &lb[x][y];
            JudgeStu(adjx, adjy);
        }
    }

    listOpen.sort(cmp);
    int tx = listOpen.front().x;
    int ty = listOpen.front().y;
    if (ManhattanD(tx, ty) > 0)
    {
        FindPath(tx, ty);
    }
}

// Print the maze with the path.
void PrintPath()
{
    // Traverse from the exit to find a path.
    PATHFIND *ip = &lb[length - 1][width - 1];
    while (ip)
    {
        lb[ip->x][ip->y].isPath = 1;
        ip = ip->parent;
    }

    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            if (lb[i][j].isRoad)
            {
                if (lb[i][j].isPath)
                {
                    printf(PATH);
                }
                else if ((i == 2 && j == 1) || (i == length - 1 && j == width))
                {
                    printf(GATE);
                }
                else
                {
                    printf(ROAD);
                }
            }
            else
            {
                printf(WALL);
            }
        }
        printf("\n");
    }
    printf("Pathfinding Procedure Success. \n");
}

void Pathfinding()
{
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            lb[i][j].x = i;
            lb[i][j].y = j;
        }
    }

    RemoveFromOpen(2, 2);
    lb[2][2].cost = 0;
    lb[2][2].status = -1;
    FindPath(2, 2);

    PrintPath();
}

#pragma endregion

int main()
{
    printf("Please input the length and the width of the maze. \n");
    while (scanf("%d%d", &length, &width))
    {
        try
        {
            if (!((length > 1) && (width > 1)))
            {
                throw - 1;
            }
        }
        catch (int error)
        {
            if (error == -1)
            {
                printf("Please input again: \n");
                printf("The side lengths should be odd and not less than 3. \n");
                continue;
            }
        }
        break;
    }
    getchar();
    system("clear");
    GenerateMaze();
    printf("Press [Enter] to find the shortest path.\n");
    getchar();

    system("clear");
    ReadMaze();
    Pathfinding();
}
