#ifndef __MAZE_PRO_H__
#define __MAZE_PRO_H__
#include <iostream>
#include <vector>
#include <stack>

struct Point
{
    int x;
    int y;

    Point(int _x, int _y) :x(_x), y(_y) {}

    bool operator==(Point _point) { return (x == _point.x && y == _point.y); }
};

template<int _row, int _col>
class Maze
{
public:
    Maze() {}

    Maze<_row, _col>(const std::vector<std::vector<int>>& _maze, const Point& _start = Point(0, 0), const Point& _end = Point(_row - 1, _col - 1))
        :start(_start), end(_end), row(_row), col(_col)
    {
        maze = _maze;
        maze[start.x][start.y] = maze[end.x][end.y] = 0;
    }

    Point& get_start() { return start; }

    void print()
    {
        for (int i = 0;i < col + 2;i++)
        {
            if (i >= 1 && i <= col)
                std::cout << "* ";
            else
                std::cout << "# ";
        }
        std::cout << std::endl;

        for (int i = 0;i < row;i++)
        {
            std::cout << "* ";
            for (int j = 0;j < col;j++)
            {
                if (Point(i, j) == start)
                {
                    std::cout << "S ";
                    maze[i][j] = 0;
                    continue;
                }
                else if (Point(i, j) == end)
                {
                    std::cout << "E ";
                    maze[i][j] = 0;
                    continue;
                }
                else if (maze[i][j] == 0)
                {
                    std::cout << "  ";
                    continue;
                }
                else if (maze[i][j] == -1)
                {
                    std::cout << "X ";
                    maze[i][j] = 0;
                    continue;
                }
                else
                {
                    std::cout << "¨€ ";
                    continue;
                }
            }
            std::cout << "* " << std::endl;
        }
        for (int i = 0;i < col + 2;i++)
        {
            if (i >= 1 && i <= col)
                std::cout << "* ";
            else
                std::cout << "# ";
        }
        std::cout << std::endl;
    }

    bool IsValid(const Point& _point)
    {
        return (_point.x >= 0 && _point.x < row && _point.y >= 0 && _point.y < col && maze[_point.x][_point.y] == 0);
    }

    bool SolvePuzzle()
    {
        std::stack<Point> maze_point;
        maze_point.push(start);

        std::vector<std::vector<bool>> IsVisited(row, std::vector<bool>(col, false));
        IsVisited[start.x][start.y] = true;

        int move_x[] = { -1, 0, 1,-1, 1,-1, 0, 1 };
        int move_y[] = { -1,-1,-1, 0, 0, 1, 1, 1 };

        while (!maze_point.empty())
        {
            Point cur = maze_point.top();

            if (cur == end)
            {
                while (!maze_point.empty())
                {
                    cur = maze_point.top();
                    maze[cur.x][cur.y] = -1;
                    maze_point.pop();
                }
                return true;
            }

            bool IsSuccess = false;

            for (int i = 0;i < 8;i++)
            {
                Point n_cur(cur.x + move_x[i], cur.y + move_y[i]);
                if (IsValid(n_cur) && !IsVisited[n_cur.x][n_cur.y])
                {
                    maze_point.push(n_cur);
                    IsVisited[n_cur.x][n_cur.y] = true;
                    IsSuccess = true;
                    break;
                }
            }

            if (!IsSuccess)
            {
                maze_point.pop();
            }
        }

        return false;
    }

    bool SolvePuzzle_Recursive(Point& cur)
    {
        if (cur == end)
        {
            maze[cur.x][cur.y] = -1;
            return true;
        }

        int move_x[] = { -1, 0, 1,-1, 1,-1, 0, 1 };
        int move_y[] = { -1,-1,-1, 0, 0, 1, 1, 1 };

        maze[cur.x][cur.y] = -1;

        for (int i = 0;i < 8;i++)
        {
            Point n_cur(cur.x + move_x[i], cur.y + move_y[i]);
            if (IsValid(n_cur))
                if (SolvePuzzle_Recursive(n_cur))
                    return true;
        }

        maze[cur.x][cur.y] = 0;
        return false;
    }

private:
    std::vector<std::vector<int>> maze;
    int row;
    int col;
    Point start;
    Point end;
};

#endif /* end maze_pro */
