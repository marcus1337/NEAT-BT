
#include <vector>

#ifndef NODE_H
#define NODE_H

enum NodeType {
    INTERIOR = 0,
    DECORATOR = 1,
    ACTION = 2,
    CONDITION = 3
};

class Node {

public:
    std::vector<Node> children;

    NodeType type;
    int ID;
    bool enabled = true;

    void addChild(Node node);

    bool isParent();
    bool isEmptyParent();

    static int maxInteriorID, maxDecoratorID, maxActionID, maxConditionID;
    static Node makeRandomInterior();
    static Node makeRandomDecorator();
    static Node makeRandomAction();
    static Node makeRandomCondition();

    bool operator< (const Node &right) const;
    bool operator==(Node const&) const;
};

#endif