
#include "Utils.h"
#include "Tree.h"
#include <tuple>
#include <vector>

#include "TreeIterator.h"

#ifndef MUTATE_H
#define MUTATE_H

class Mutate {
    bool shouldMutate(float chance);
    void replaceRandomly(Node* node);
    Node makeRandomNode();

    Node* getRandomInterior(Tree& tree);
    Node* getEmptyParentChild(Node* node);
    std::vector<Node*> getInteriors(Tree& tree);

    std::vector<std::tuple<Node*, int>> getDeletableNodes(Tree& tree);
    bool hasMultipleActions(Tree& tree);
public:

    float mutateChance = 0.01f;

    void addNodeMutate(Tree& tree);
    void deleteNodeMutate(Tree& tree);
    void replaceMutate(Tree& tree);

    void mutateTree(Tree& tree);
};

#endif