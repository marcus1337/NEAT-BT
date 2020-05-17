#include "TreeIterator.h"


void TreeIterator::addChildrenToQueue(Node* node) {
    if(node->isParent()) //not really a needed check
        for (auto& n : node->children)
            unvisited.push(&n);
}

Node* TreeIterator::popNodeQueue() {
    Node* node = unvisited.front();
    unvisited.pop();
    return node;
}