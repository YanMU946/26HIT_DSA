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
        { 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, },
        { 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, },
        { 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, },
        { 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, },
        });
    muggle.print();

    if (muggle.SolvePuzzle())//·ÇµÝ¹é
    {
        std::cout << "Planned successfully" << std::endl;
        muggle.print();
    }
    else
    {
        std::cout << "Failed" << std::endl;
        muggle.print();
    }

    if (muggle.SolvePuzzle_Recursive(muggle.get_start()))//µÝ¹é
    {
        std::cout << "Planned successfully" << std::endl;
        muggle.print();
    }
    else
    {
        std::cout << "Failed" << std::endl;
        muggle.print();
    }
    return 0;
}

