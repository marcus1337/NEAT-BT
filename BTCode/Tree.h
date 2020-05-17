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
    int getNumberOfNodesOfType(NodeType nodeType);
    int getNumberOfNodes();

    Node* getRandomNonRootNode();
    Node* getRandomNode();
    Node* getNodeAtIndex(int index);
    Node* getEmptyParent();
    Node* getNodeWithEmptyChild();
    bool removeEmptyChildrenFromNode(Node* node);
    void removeAllEmptyChildren();
    bool containsActionNode();

    Node root;
    int fitness = 0;

    std::vector<Node> getNodesCopy();
    bool equals(Tree& other);

    void deleteLeaf(int position);
    void deleteCondition(int position);
};

#endif