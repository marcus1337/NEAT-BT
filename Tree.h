#include "Node.h"
#include <queue>
#include <vector>

#ifndef TREE_H
#define TREE_H

class Tree {

    std::queue<Node*> makeNodeQueue();
    void addParentsToQueue(std::queue<Node*>& nodes, Node* node);
    bool removeAllEmptyLeaves();
    Node* popNodeQueue(std::queue<Node*>& nodes);

public:

    Tree();
    Tree getValidTree();

    int getNumberParentNodes();

    Node* getEmptyParent();
    Node* getNodeWithEmptyChild();
    bool removeEmptyChildrenFromNode(Node* node);
    void removeAllEmptyChildren();
    bool containsActionNode();

    Node root;
    int fitness;

    std::vector<Node> getNodes();

};

#endif