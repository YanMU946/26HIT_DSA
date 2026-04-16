#include "maze_pro.h"

int main()
{
    Maze<14, 12> muggle({
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
        { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
        { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, },
        { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, },
        { 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, },
        { 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, },
        { 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, },
        { 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, },
        { 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, },
        { 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, },
        });
    muggle.print();

    if (muggle.SolvePuzzle())
    {
        std::cout << "Planned successfully" << std::endl;
        muggle.print();
    }
    else
        std::cout << "Failed" << std::endl;
        
    if (muggle.SolvePuzzle_Recursive())
    {
        std::cout << "Planned successfully" << std::endl;
        muggle.print();
    }
    else
        std::cout << "Failed" << std::endl;
    return 0;
}

