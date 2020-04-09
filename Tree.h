#include "Node.h"
#include <queue>

#ifndef TREE_H
#define TREE_H


class Tree {

    std::queue<Node*> makeNodeQueue();
    void addParentsToQueue(std::queue<Node*>& nodes, Node* node);
    bool removeAllEmptyLeaves();
    Node* popNodeQueue(std::queue<Node*>& nodes);

public:

    Tree() {
        root = Node::makeRandomInterior();
        root.addChild(Node::makeRandomAction());
    }

    int getNumberParentNodes();

    Node* getNodeWithEmptyChild();
    bool removeEmptyChildrenFromNode(Node* node);
    void removeAllEmptyChildren();

    Node root;
    int fitness;

};

#endif