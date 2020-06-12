#include <iostream>
#include "MazeGenerator.h"
#include "PathFinder.h"
int main()
{
    while (1)
    {
        system("clear");
        std::cout << "...\n";
        int l;
        int w;
        std::cin >> l >> w;
        getchar();

        system("clear");
        MazeGenerator m(l, w);
        getchar();

        system("clear");
        PathFinder p(m);
        getchar();
    }
}