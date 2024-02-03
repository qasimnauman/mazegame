#pragma once
#ifndef QUEUE
#define QUEUE
#include "Vertex.h"
struct Node {
    Vertex* data;
    Node* next;
    Node(Vertex* vertex)
    {
        data = vertex;
        next = nullptr;
    }

};

class MyQueue {
private:

    Node* frontPtr;
    Node* rearPtr;

public:
    MyQueue() : frontPtr(nullptr), rearPtr(nullptr) {}

    void enqueue(Vertex* vertex) {
        Node* newNode = new Node(vertex);
        if (rearPtr == nullptr) {
            frontPtr = rearPtr = newNode;
        }
        else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
    }

    void dequeue() {
        if (frontPtr == nullptr) {
            return;
        }

        Node* temp = frontPtr;
        frontPtr = frontPtr->next;
        if (frontPtr == nullptr) {
            rearPtr = nullptr;
        }
        delete temp;
    }

    bool empty() const {
        return frontPtr == nullptr;
    }

    Vertex* front() const {
        if (frontPtr != nullptr) {
            return frontPtr->data;
        }
        return nullptr;
    }
};

#endif // !MY_QUEUE
