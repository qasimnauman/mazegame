#ifndef __MAZE__
#define __MAZE__
#include "Vertex.h"

using namespace std;

class IMazeReader {
public:
    virtual void isVertex(int y, int x, bool& top, bool& down, bool& left, bool& right, bool& isGoal) = 0;
    virtual void setSize(size_t& row, size_t& col) = 0;
};

class Maze {

private:
    list<Vertex*> _maze;
    size_t _row = 0;
    size_t _col = 0;
    Vertex* goal[2];

public:
    using iterator = list<Vertex*>::iterator;

    Maze() {
        goal[0] = nullptr;
        goal[1] = nullptr;
    }

    ~Maze() {
    }

    void setSize(size_t row, size_t col) {
        _row = row;
        _col = col;
    }

    size_t getColumn() {
        return _col;
    }

    size_t getRow() {
        return _row;
    }

    void push_back(Vertex* v) {
        _maze.push_back(v);
    }

    iterator begin() {
        return _maze.begin();
    }


    iterator end() {
        return _maze.end();
    }



    int listSize() const {
        return _maze.size();
    }

    bool empty() const {
        return _maze.empty();
    }

    void setMaze(IMazeReader& mb) {
        mb.setSize(_row, _col);
        bool isGoal = false;

        int* top_count = new int[getColumn()]();
        Vertex** top_next = new Vertex * [getColumn()];
        list<Vertex*> reduntant;

        bool path_top = false, path_down = false, path_right = false, path_left = false;
        for (int line = 0; line < getRow(); ++line) {
            int right_count = 0;
            Vertex* left_next = nullptr;

            for (int index = 0; index < getColumn(); ++index) {
                int count = 0;
                path_top = false; path_down = false; path_right = false; path_left = false;

                mb.isVertex(line, index, path_top, path_down, path_left, path_right, isGoal);

                if (path_top)
                    ++count;
                if (path_down)
                    ++count;
                if (path_left)
                    ++count;
                if (path_right)
                    ++count;

                bool left_right = bool(path_left != path_right);
                bool up_down = bool(path_top != path_down);
                bool all = bool(path_top && path_down && path_left && path_right);

                if (left_right || up_down || all || isGoal) {
                    Vertex* current = new Vertex;
                    current->setPosition(line, index);

                    if (path_top) {
                        current->setTop(top_next[index], top_count[index] + 1);
                        top_next[index]->setDown(current, top_count[index] + 1);
                    }

                    if (path_left) {
                        current->setLeft(left_next, right_count + 1);
                        left_next->setRight(current, right_count + 1);
                    }

                    top_next[index] = left_next = current;

                    top_count[index] = 0;
                    right_count = 0;

                    if (isGoal) {
                        addToGoal(current);
                    }

                    if (isGoal || count != 2) {
                        push_back(current);
                        isGoal = false;
                    }
                    else {
                        reduntant.push_back(current);
                    }
                }
                else {
                    ++right_count;
                    ++top_count[index];
                }
            }
        }

        for (iterator it = reduntant.begin(); it != reduntant.end(); ++it) {
            Vertex* x = *it;

        }

        delete[] top_next;
        if (!maze_begin()) addToGoal(*begin());
        if (!maze_end()) addToGoal(*--end());
    }

    void addToGoal(Vertex* v) {
        if (!goal[0])
            goal[0] = v;
        else
            goal[1] = v;
    }

    Vertex* maze_begin() {
        return goal[0];
    }

    Vertex* maze_end() {
        return goal[1];
    }


};

#endif // !__MAZE__
