
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
    NodeType type;
    int ID;
    bool enabled;
    std::vector<Node> children;

    static int maxInteriorID, maxDecoratorID, maxActionID, maxConditionID;
};

#endif