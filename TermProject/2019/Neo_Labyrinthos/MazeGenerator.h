#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <vector>
#include <iostream>
#include <list>
#include <unistd.h>

#define BLACK "\033[40m  \033[0m"
#define RED "\033[41m  \033[0m"
#define GREEN "\033[42m  \033[0m"
#define YELLOW "\033[43m  \033[0m"
#define BLUE "\033[44m  \033[0m"
#define PURPLE "\033[45m  \033[0m"
#define DARK_GREEN "\033[46m  \033[0m"
#define WHITE "\033[47m  \033[0m"
#define TRANSPARENT "  "

class MazeGenerator
{
    friend class PathFinder;

public:
    MazeGenerator(int, int);

private:
    void PrintMaze();
    void PrintProcess();
    void Add2List(int, int);
    struct MAZE
    {
        int x;
        int y;
        int state;
        bool isBolder;
        bool isInS;
    };
    enum
    {
        WALL = -1,
        ROAD = 1,
        GATE = 2
    };
    std::vector<std::vector<MAZE>> maze;
    std::list<MAZE> listS;
    int length;
    int width;
    int gate;
    int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
};

#endif
