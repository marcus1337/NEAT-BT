#include "Tree.h"
#include <vector>
#include "Specie.h"

#ifndef EVOLVER_H
#define EVOLVER_H

class Evolver {
public:
    int numChildrenLeft = 0;
    std::vector<Tree> makeNewGeneration(std::vector<Tree>& trees);
    void breedFitnessBased(int numKids, std::vector<Tree>& newTrees);
    void breedElitismOfSpecies(int numKids, std::vector<Tree>& newTrees);
    void breedChild(Specie& specie, std::vector<Tree>& newTrees);
};

#endif