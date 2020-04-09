
#include "Node.h"
#include <queue>

#ifndef TREEITERATOR_H
#define TREEITERATOR_H

class TreeIterator {
    std::queue<Node*> unvisited;
    void addChildrenToQueue(Node* node);
    Node* popNodeQueue();

public:

    TreeIterator(Node& _root) { unvisited.push(&_root); }

    Node* next() {
        Node* node = popNodeQueue();
        addChildrenToQueue(node);
        return node;
    }
    bool hasNext() { return !unvisited.empty(); };

};


#endif