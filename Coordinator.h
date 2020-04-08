
#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "Tree.h"
#include <vector>

class Coordinator {
public:

    std::vector<Tree> trees;


    void init(int numTrees, int maxInteriorID, int maxDecoratorID, int maxActionID, int maxConditionID) {
        Node::maxInteriorID = maxInteriorID;
        Node::maxDecoratorID = maxDecoratorID;
        Node::maxActionID = maxActionID;
        Node::maxConditionID = maxConditionID;

        trees.resize(numTrees);
    }

};

#endif