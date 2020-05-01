#include "Breeder.h"
#include "Utils.h"
#include <algorithm>

std::vector<Tree> Breeder::makeNewGeneration(std::vector<Tree*> singleTrees, std::vector<std::pair<Tree*, Tree*>> pairedTrees) {
    std::vector<Tree> trees;
    numChildrenLeft = populationSize;
    int pairCounter = 0;
    int singleCounter = 0;

    while (numChildrenLeft > populationSize / 2) {
        breedCrossover(trees, pairedTrees[pairCounter].first, pairedTrees[pairCounter].second);
        numChildrenLeft--;
        pairCounter++;
    }

    while (numChildrenLeft > 0) {
        trees.push_back(*singleTrees[singleCounter]);
        numChildrenLeft--;
        singleCounter++;
    }

    return trees;
}

void Breeder::breedCrossover(std::vector<Tree>& newTrees, Tree* t1, Tree* t2) {
    Tree child;
    crossOver(child, t1, t2);
    newTrees.push_back(child);
}

void Breeder::crossOver(Tree& child, Tree* n1, Tree* n2) {
    if (n1->fitness < n2->fitness)
        Utils::swapPointers<Tree>(&n1, &n2);
    child = *n1;
    Node* node1 = child.getRandomNode();
    Node* node2 = n2->getRandomNode();
    *node1 = *node2;
    if (child.getNumberOfNodesOfType(ACTION) == 0)
        child = *n1;
}
