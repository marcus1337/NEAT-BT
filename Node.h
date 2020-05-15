
#include <vector>

#ifndef NODE_H
#define NODE_H

enum NodeType {
    OTHER_INTERIOR = 0,
    UNORDERED_INTERIOR = 1,
    DECORATOR = 2,
    ACTION = 3,
    CONDITION = 4
};

class Node {

public:
    std::vector<Node> children;

    NodeType type;
    int ID;

    void addChild(Node node);

    bool isParent();
    bool isEmptyParent();

    static int maxInteriorID, maxDecoratorID, maxActionID, maxConditionID;
    static Node makeRandomOtherInterior();
    static Node makeRandomDecorator();
    static Node makeRandomAction();
    static Node makeRandomCondition();

    bool operator< (const Node &right) const;
    bool operator==(Node const&) const;
    bool operator!=(Node const&) const;
};

#endif