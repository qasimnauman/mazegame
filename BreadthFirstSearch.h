#ifndef BREADTHFIRSTSEARCH
#define BREADTHFIRSTSEARCH

#include "Path.h"
#include "Queue.h" 

class BreadthFirstSearch : public Path {
public:
    void findPath(Vertex* start, Vertex* end) {
        if (!intialCheck(start, end))
            return;

        MyQueue q;
        q.enqueue(start);
        start->setLength(0);
        Vertex* next = nullptr;

        while (!q.empty()) {
            next = q.front();
            q.dequeue();

            if (next->isVisted())
                continue;


            next->setVisted(true);

            if (next == end)
                break;


            for (int i = 0; i < next->edgesSize(); ++i) {
                Vertex::Edge& edge = next->getEdges()[i];
                if (edge.isReachable() && !(edge.getVertex()->isVisted())) {
                    q.enqueue(edge.getVertex());
                    edge.getVertex()->setLength(next->getLength() + 1);
                    addToAnimate(next, edge.getVertex());
                }
            }
        }

        if (!end->isVisted()) return; // end cannot be reached

        trace(end, start, next->getLength() - 1);
    }

private:
    bool trace(Vertex* start, Vertex* end, int count) {
        path.push_front(start);

        for (int i = 0; i < start->edgesSize(); ++i) {
            Vertex::Edge& edge = start->getEdges()[i];
            if (edge.isReachable() && edge.getVertex()->getLength() == count) {
                trace(edge.getVertex(), start, count - 1);
                return true;
            }
        }

        return false;
    }
};

#endif // !BREADTHFIRSTSEARCH
