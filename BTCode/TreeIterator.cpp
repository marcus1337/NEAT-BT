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

TreeIterator::TreeIterator(Node& _root) {
    unvisited.push(InfoNode(&_root));
}

Node* TreeIterator::next() {
    Node* node = popNodeQueue();
    addChildrenToQueue(node);
    return node;
}
InfoNode TreeIterator::nextInfo() {
    InfoNode node = unvisited.front();
    unvisited.pop();
    addChildrenToQueue(node.node);
    return node;
}

bool TreeIterator::hasNext() { return !unvisited.empty(); };