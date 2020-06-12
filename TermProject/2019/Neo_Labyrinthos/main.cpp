#include <iostream>
#include "MazeGenerator.h"
#include "PathFinder.h"

int main()
{
    while (1)
    {
        system("printf \"\033c\"");
        std::cout << "(length, width) = ";
        int l = 1;
        int w = 1;
        std::cin >> l >> w;
        getchar();

        system("printf \"\033c\"");
        MazeGenerator m(l, w);
        getchar();

        system("printf \"\033c\"");
        PathFinder p(m);
        getchar();
    }
}