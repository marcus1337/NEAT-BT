#include "Tree.h"
#include <vector>
#include "Specie.h"

#ifndef BREEDER_H
#define BREEDER_H

class Breeder {
    int numMadeTrees = 0;
    void crossOver(Tree& child, Tree* n1, Tree* n2);
    bool isCrossOverOk(Tree* n1, Tree* n2);
    bool cloneChildAndCheckCrossOver(Tree& child, Tree* n1, Tree* n2);

public:
    int populationSize = 1;

    std::vector<Tree> makeNewGeneration(std::vector<Tree*> singleTrees, std::vector<std::pair<Tree*, Tree*>> pairedTrees);


    void breedCrossover(std::vector<Tree>& newTrees, Tree* t1, Tree* t2);

};

#endif