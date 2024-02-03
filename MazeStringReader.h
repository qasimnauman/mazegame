#ifndef _MAZESTRINGREADER_
#define _MAZESTRINGREADER_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class MazeStringReader : public IMazeReader {

private:
    int x_max, y_max; // max size of maze
    int _goalPos[2][2]; // stores position of start and end goal
    bool usingDefault = true; // does file specify start and end goal
    vector<string> maze_txt; // to store maze file

public:
    MazeStringReader() {}

    bool getFile(string file) {
        maze_txt.clear();
        ifstream in(file);
        if (in.fail()) {
            cout << "File not found!\n";
            return false;
        }
        vector<string> maze;
        string buffer;
        while (!in.eof()) {
            getline(in, buffer, '\n');
            maze_txt.push_back(buffer);
        }
        y_max = ((maze_txt.size() - 1) / 2) - 1;
        x_max = ((maze_txt[0].size() - 1) / 4) - 1;
        return true;
    }

    bool isOuter(size_t row, size_t col) {
        for (int i = 0; i < 2; ++i) {
            if (_goalPos[i][0] == row && _goalPos[i][1] == col)
                return true;
        }
        return false;
    }

    void isVertex(int y, int x, bool& top, bool& down, bool& left, bool& right, bool& isGoal) {
        if (!usingDefault && isOuter(y, x))
            isGoal = true;

        if (maze_txt[(y * 2) + 0][(x * 4) + 1] == ' ') // top
            if (y != 0)
                top = true;
            else if (usingDefault) {
                isGoal = true;
            }

        if (maze_txt[(y * 2) + 1][x * 4] == ' ') // left
            if (x != 0)
                left = true;
            else if (usingDefault) {
                isGoal = true;
            }

        if (maze_txt[(y * 2) + 1][(x * 4) + 4] == ' ')
            if (x != x_max) // right
                right = true;
            else if (usingDefault) {
                isGoal = true;
            }

        if (maze_txt[(y * 2) + 2][(x * 4) + 1] == ' ') // down
            if (y != y_max)
                down = true;
            else if (usingDefault) {
                isGoal = true;
            }
    }

    void setSize(size_t& row, size_t& col) {
        row = y_max + 1;
        col = x_max + 1;
    }

    int getRow() {
        return y_max;
    }

    int getColumn() {
        return x_max;
    }

    vector<string>& getText() {
        return maze_txt;
    }
};

#endif // !_MAZESTRINGREADER_