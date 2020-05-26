
#include "Utils.h"
#include "Tree.h"
#include <tuple>
#include <vector>

#include "TreeIterator.h"
#include "MutationRateControl.h"

#ifndef MUTATE_H
#define MUTATE_H

class Mutate {
    bool shouldMutate(float chance);
    void replaceRandomly(Node* node);
    Node makeRandomNode();
    Node makeRandomReplaceInterior(Node* oldNode);

    Node* getRandomInterior(Tree& tree);
    Node* getEmptyParentChild(Node* node);
    std::vector<Node*> getInteriors(Tree& tree);

    std::vector<std::tuple<Node*, int>> getDeletableNodes(Tree& tree);
    bool hasMultipleActions(Tree& tree);

    void limitTreeSize(Tree& tree);

    void replaceLeafRandomly(Node* node);
    void replaceInteriorRandomly(Node* node);
    void replaceRootRandomly(Node* node);

    MutationRateControl mutationRateControl;


public:
    int maxTreeNodes = 30;

    float mutateChance = 0.05f;

    void addNodeMutate(Tree& tree);
    void deleteNodeMutate(Tree& tree);
    void replaceMutate(Tree& tree);

    void mutateTree(Tree& tree);
    void mutateTrees(std::vector<Tree>& trees);

    void modifyMutationRate(std::vector<Tree>& trees);
};

#endif