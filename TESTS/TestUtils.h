#pragma once
#include "../BTCode/Node.h"
#include "../BTCode/IOHandler.h"
#include "../BTCode/Tree.h"
#include "../BTCode/Coordinator.h"
#include "../BTCode/Mutate.h"

class TestUtils {
public:

    static Tree getValidTree(Tree& prevTree);
    static Tree getRandomizedTree(int numNodes);

    static void setMaxNodeIDs(int maxNum);

};