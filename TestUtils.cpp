#include "TestUtils.h"

Tree TestUtils::getValidTree(Tree& prevTree) {
    Tree tree = prevTree;
    tree.removeAllEmptyChildren();
    return tree;
}