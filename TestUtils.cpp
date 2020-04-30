#include "TestUtils.h"

Tree TestUtils::getValidTree(Tree& prevTree) {
    Tree tree = prevTree;
    tree.removeAllEmptyChildren();
    return tree;
}

Tree TestUtils::getRandomizedTree(int numNodes) {
    Mutate mutater;
    mutater.mutateChance = 1;
    Tree tree;
    for (int i = 0; i < numNodes; i++)
        mutater.addNodeMutate(tree);
    return tree;
}

void TestUtils::setMaxNodeIDs(int maxNum) {
    Node::maxInteriorID = maxNum;
    Node::maxDecoratorID = maxNum;
    Node::maxActionID = maxNum;
    Node::maxConditionID = maxNum;
}