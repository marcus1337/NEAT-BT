#include "TreeIterator.h"


void TreeIterator::addChildrenToQueue(Node* node) {
    if (node->isParent()) //not really a needed check
        for (size_t i = 0; i < node->children.size(); i++)
            unvisited.push(InfoNode(&node->children[i],node));
}

Node* TreeIterator::popNodeQueue() {
    Node* node = unvisited.front().node;
    unvisited.pop();
    return node;
}