#ifndef __VERTEX__
#define __VERTEX__

#include <list>
#include <limits.h>
using namespace std;

struct Coordinates {
    int row = -1;
    int col = -1;
};

class Vertex {
public:
    class Edge {
    public:
        Edge() {}

        using iterator = list<Coordinates>::iterator;
        using const_iterator = list<Coordinates>::const_iterator;

        iterator begin() {
            return intermidate.begin();
        }

        const_iterator begin() const {
            return intermidate.cbegin();
        }

        iterator end() {
            return intermidate.end();
        }

        const_iterator end() const {
            return intermidate.cend();
        }

        void push_front_intermidate(int row, int col) {
            Coordinates toPush;
            toPush.row = row;
            toPush.col = col;
            intermidate.push_front(toPush);
        }

        void push_back_intermidate(int row, int col) {
            Coordinates toPush;
            toPush.row = row;
            toPush.col = col;
            intermidate.push_back(toPush);
        }

        bool isReachable() const {
            return to;
        }

        int getEdgeLength() const {
            return len;
        }

        Vertex* getVertex() {
            return to;
        }

        void set(Vertex* v, int length) {
            to = v;
            len = length;
        }

        ~Edge() {
            to = nullptr;
        }

    private:
        int len = INT_MAX; // length set to infinity
        Vertex* to = nullptr; // to which vertex
        list<Coordinates> intermidate; // important intermediate points

        friend class Vertex;
    };

private:
    bool visted = false; // to check if cell is visited 
    int len = INT_MAX; // length set to infinity 

    static const int EDGE_SIZE = 4;

    Edge directions[EDGE_SIZE]; // Edges to top down left right cells

    // position of cell of in maze
    int row = -1;
    int col = -1;

public:

    using iterator = Edge*;
    using const_iterator = const Edge*;

    ~Vertex() {}

    iterator begin() {
        return directions;
    }

    const_iterator begin() const {
        return directions;
    }

    iterator end() {
        return directions + EDGE_SIZE;
    }

    const_iterator end() const {
        return directions + EDGE_SIZE;
    }

    Edge* getEdges() {
        return directions;
    }

    int edgesSize() {
        return EDGE_SIZE;
    }

    int getRow() {
        return row;
    }

    int getColumn() {
        return col;
    }

    void setPosition(int _row, int _col) {
        row = _row;
        col = _col;
    }


    void setTop(Vertex* v, int len = 1) {
        directions[0].to = v;
        directions[0].len = len;
    }

    void setDown(Vertex* v, int len = 1) {
        directions[1].to = v;
        directions[1].len = len;
    }

    void setLeft(Vertex* v, int len = 1) {
        directions[2].to = v;
        directions[2].len = len;
    }

    void setRight(Vertex* v, int len = 1) {
        directions[3].to = v;
        directions[3].len = len;
    }


    void setLength(int _len) {
        len = _len;
    }

    int getLength() {
        return len;
    }

    void setVisted(bool b) {
        visted = b;
    }

    bool isVisted() {
        return visted;
    }

    void reset() {
        visted = false;
        len = INT_MAX;
    }

    Edge& connectingEdge(Vertex* to) {
        for (int i = 0; i < edgesSize(); ++i) {
            if (getEdges()[i].getVertex() == to) {
                return getEdges()[i];
            }
        }
        throw;
    }
};

#endif // !__VERTEX__
