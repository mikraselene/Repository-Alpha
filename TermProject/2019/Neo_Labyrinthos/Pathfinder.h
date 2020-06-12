#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <list>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>

#include "MazeGenerator.h"

class PathFinder
{
public:
    PathFinder(MazeGenerator);

private:
    void RemoveFromOpen(int, int);
    void Find(int, int);
    int HeuristicDistance(int, int, int);
    void PrintPath();
    void PrintProcess();
    enum
    {
        NON_HEURISTIC = 0,
        MANHATTAN = 1,
        CHEBYSHEV = 2,
        EUCLIDEAN = 3,
    };
    enum
    {
        OPEN = 1,
        UNDEFINED = 0,
        CLOSED = -1,
    };
    struct MAZE
    {
        int x;
        int y;
        int state;
        bool isRoad;
        bool isPath;
        int priority;   // F(P)
        int cost;       // G(P)
        int estimation; // H(P)
        MAZE *parent;
        MAZE *child;
    };
    std::vector<std::vector<MAZE>> maze;
    std::list<MAZE> listOpen;
    int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int length;
    int width;
    int gate;
};

#endif
