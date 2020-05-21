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
        numMadeTrees+=2;
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
    Tree child1;
    Tree child2;
    crossOver(child1, child2, t1, t2);
    newTrees.push_back(child1);
    newTrees.push_back(child2);
}

void Breeder::crossOver(Tree& child1, Tree& child2, Tree* n1, Tree* n2) {
    child1 = *n1;
    child2 = *n2;

    if (!isCrossOverOk(n1, n2))
        return;

    Node* node1 = child1.getRandomNonRootNode();
    Node* node2 = child2.getRandomNonRootNode();
    auto tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
}

bool Breeder::isCrossOverOk(Tree* n1, Tree* n2) {
    int numBranches1 = n1->getNumBranches();
    int numBranches2 = n2->getNumBranches();
    return numBranches1 >= 3 && numBranches2 >= 3;
}
