#include "Node.h"

#ifndef TREE_H
#define TREE_H


class Tree {
public:

    Tree() {
        root = Node::makeRandomInterior();
        root.addChild(Node::makeRandomAction());
    }

    int getNumberParentNodes();

    Node root;
    int fitness;

};

#endif