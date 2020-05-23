
#include "Node.h"
#include <queue>

#ifndef INFONODE_H
#define INFONODE_H

class InfoNode {
public:
    Node* node;
    Node* parentNode = nullptr;
    InfoNode(Node* _node) : node(_node) {}
    InfoNode(Node* _node, Node* _parentNode) : node(_node), parentNode(_parentNode) {};
};

#endif


#ifndef TREEITERATOR_H
#define TREEITERATOR_H


class TreeIterator {
    std::queue<InfoNode> unvisited;
    void addChildrenToQueue(Node* node);
    Node* popNodeQueue();

public:

    TreeIterator(Node& _root) {
        unvisited.push(InfoNode(&_root)); 
    }

    Node* next() {
        Node* node = popNodeQueue();
        addChildrenToQueue(node);
        return node;
    }
    InfoNode nextInfo() {
        InfoNode node = unvisited.front();
        unvisited.pop();
        addChildrenToQueue(node.node);
        return node;
    }

    bool hasNext() { return !unvisited.empty(); };

};


#endif