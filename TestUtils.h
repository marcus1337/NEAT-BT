#pragma once
#include "Node.h"
#include "IOHandler.h"
#include "Tree.h"
#include "Coordinator.h"
#include "Mutate.h"

class TestUtils {
public:

    static Tree getValidTree(Tree& prevTree);
    static Tree getRandomizedTree(int numNodes);

    static void setMaxNodeIDs(int maxNum);

};