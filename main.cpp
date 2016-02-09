
#include <iostream>
#include "disjointsets.h"
#include "mazegen.h"
#include "png.h"

int main()
{
    MazeGen m;
    m.generate(10, 10);
    std::cout << "Generate complete" << std::endl;

    PNG* unsolved = m.drawUnsolved();
    unsolved->writeToFile("unsolved.png");
    delete unsolved;
    std::cout << "drawUnsolved complete" << std::endl;

    std::vector<int> sol = m.findPath();
    std::cout << "findPath complete" << std::endl;

    //PNG* solved = m.drawSolved();
    //solved->writeToFile("solved.png");
    //delete solved;
    //std::cout << "drawSolved complete" << std::endl;

    return 0;
}
