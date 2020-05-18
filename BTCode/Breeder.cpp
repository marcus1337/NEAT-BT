#include "Breeder.h"
#include "Utils.h"
#include <algorithm>

std::vector<Tree> Breeder::makeNewGeneration(std::vector<Tree*> singleTrees, std::vector<std::pair<Tree*, Tree*>> pairedTrees) {
    std::vector<Tree> trees;
    numMadeTrees = 0;
    int pairCounter = 0;
    int singleCounter = 0;

    while (numMadeTrees < populationSize / 5) {
        breedCrossover(trees, pairedTrees[pairCounter].first, pairedTrees[pairCounter].second);
        numMadeTrees++;
        pairCounter++;
    }

    while (numMadeTrees < populationSize) {
        trees.push_back(*singleTrees[singleCounter]);
        numMadeTrees++;
        singleCounter++;
    }

    return trees;
}

void Breeder::breedCrossover(std::vector<Tree>& newTrees, Tree* t1, Tree* t2) {
    Tree child;
    crossOver(child, t1, t2);
    newTrees.push_back(child);
}

bool Breeder::cloneChildAndCheckCrossOver(Tree& child, Tree* n1, Tree* n2) {
    if (n1->fitness < n2->fitness)
        Utils::swapPointers<Tree>(&n1, &n2);
    child = *n1;
    if (!isCrossOverOk(n1, n2))
        return false;
    return true;
}

void Breeder::crossOver(Tree& child, Tree* n1, Tree* n2) {
    if (!cloneChildAndCheckCrossOver(child, n1, n2))
        return;

    Node* node1 = child.getRandomNonRootNode();
    Node* node2 = n2->getRandomNode();
    *node1 = *node2;
    child = *n1;
}

bool Breeder::isCrossOverOk(Tree* n1, Tree* n2) {
    int numBranches1 = n1->getNumBranches();
    int numBranches2 = n2->getNumBranches();
    return numBranches1 >= 5 && numBranches2 >= 5;
}
