#ifndef __PATH__
#define __PATH__

#include <list>
#include <queue>
#include "Vertex.h"
using namespace std;

struct Travel {
    Vertex* from;
    Vertex* to;
};

class Path {

protected:
    list<Vertex*> path; // path from start to end used in trace
    int count = 0; // used for iteration count
    queue<Travel> visted;

    void addToAnimate(Vertex* from, Vertex* to) {
        if (to && to->isVisted()) return;

        Travel topush;
        topush.from = from;
        topush.to = to;
        visted.push(topush);
    }


    bool intialCheck(Vertex* start, Vertex* end) {
        if (!start || !end)    // if start or end are nullptr path does not exist
            return false;

        if (start == end) { // if start equals end path found return false
            path.push_back(start);
            return false;
        }

        return true; // find path 
    }

public:
    // default constructor
    Path() {}

    // return count
    int getCount() {
        return count;
    }

    // get path
    const list<Vertex*>& getPath() {
        return path;
    }

    queue<Travel>& getVisted() {
        return visted;
    }
};
#endif // !__PATH__
