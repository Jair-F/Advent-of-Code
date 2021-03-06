#include <iostream>
#include <fstream>
#include <list>
#include <vector>

struct Point
{
    unsigned short x, y;
};

struct Line
{
    Point point1, point2;
};

int main()
{
    std::fstream input;
    //input.open("example.txt");
    input.open("part1 - input.txt");
    if (!input.good())
    {
        std::cerr << "Error while parsing the input-file!\n\n";
        return -1;
    }

    std::list<Line> lines;

    std::string line;
    while (std::getline(input, line))
    {
        unsigned short points[4]; // x1,y1,x2,y2 in this order!!
        unsigned short tmp = 0;
        unsigned short counter = 0; // position in the points-array
        for (auto iterator = line.begin(); iterator != line.end(); ++iterator)
        {
            if (*iterator >= '0' && *iterator <= '9')
            {
                tmp *= 10;
                tmp += *iterator - '0';
            }
            else if (*iterator == ',' || *iterator == ' ')
            {
                points[counter] = tmp;
                tmp = 0;
                ++counter;
            }

            if (*iterator == ' ')
            {
                while (*iterator == ' ' || *iterator == '-' || *iterator == '>' && iterator != line.end())
                {
                    ++iterator;
                }
                --iterator;
            }
        }
        points[3] = tmp;
        // copy the data in a list-vector
        Line l;
        Point p;
        p.x = points[0];
        p.y = points[1];
        l.point1 = p;
        p.x = points[2];
        p.y = points[3];
        l.point2 = p;
        lines.push_back(l);
    }

    // printing points
    //for (auto &line : lines)
    //{
    //    std::cout << line.point1.x << ',' << line.point1.y << " -> " << line.point2.x << ',' << line.point2.y << '\n';
    //}
    //std::cout << "\n\n\n\n";

    std::list<Line> straight_lines; // horizontal and vertical

    // extracting horizontal and vertical lines
    for (Line &l : lines)
    {
        if (l.point1.x == l.point2.x || l.point1.y == l.point2.y)
        {
            straight_lines.push_back(l);
        }
    }

    // getting longest x-and y-line
    unsigned short longest_x = 0, longest_y = 0;
    for (Line &l : straight_lines)
    {
        longest_x = l.point1.x > longest_x ? l.point1.x : longest_x;
        longest_x = l.point2.x > longest_x ? l.point2.x : longest_x;

        longest_y = l.point1.x > longest_y ? l.point1.x : longest_y;
        longest_y = l.point2.x > longest_y ? l.point2.x : longest_y;
    }

    ++longest_y;
    ++longest_x;

    std::vector<std::vector<unsigned short>> board(longest_x); // board where we save how many lines cover on each point
    for (unsigned short i = 0; i < board.size(); ++i)
    { // allocating enough memory for the board
        //board[i].reserve(longest_y);
        board[i].resize(longest_y);
    }

    // printing horizontal lines
    //for (auto &line : straight_lines)
    //{
    //    std::cout << line.point1.x << ',' << line.point1.y << " -> " << line.point2.x << ',' << line.point2.y << '\n';
    //}

    for (Line &l : straight_lines)
    {
        // "draw" the lines on the board...
        if (l.point1.x == l.point2.x)
        {
            unsigned short starting_point, end_point;
            starting_point = l.point1.y > l.point2.y ? l.point2.y : l.point1.y; // the lowest point - to start from
            end_point = l.point1.y < l.point2.y ? l.point2.y : l.point1.y;
            for (unsigned short i = starting_point; i <= end_point; ++i)
            {
                board[l.point1.x][i] += 1; // the x-point is the same at the two lines-they are vertical
            }
        }
        else if (l.point1.y == l.point2.y)
        {
            unsigned short starting_point, end_point;
            starting_point = l.point1.x > l.point2.x ? l.point2.x : l.point1.x;
            end_point = l.point1.x < l.point2.x ? l.point2.x : l.point1.x;
            for (unsigned short i = starting_point; i <= end_point; ++i)
            {
                board[i][l.point1.y] += 1;
            }
        }
    }

    unsigned short overlapping_point_counter = 0;

    for (auto &row : board)
    {
        for (auto &point : row)
        {
            if (point >= 2)
            {
                ++overlapping_point_counter;
            }
        }
    }

    // printing the board
    //for (auto &row : board)
    //{
    //    for (auto &column : row)
    //    {
    //        if (column > 0)
    //        {
    //            std::cout << column << ' ';
    //        }
    //        else
    //        {
    //            std::cout << ". ";
    //        }
    //    }
    //    std::cout << '\n';
    //}

    std::cout << overlapping_point_counter << '\n';

    return 0;
}