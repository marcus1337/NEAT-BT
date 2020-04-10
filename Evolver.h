#include "Tree.h"
#include <vector>
#include "Specie.h"
#include "Mutate.h"

#ifndef EVOLVER_H
#define EVOLVER_H

class Evolver {
    Mutate mutater;
public:
    int numChildrenLeft = 0;
    std::vector<Tree> makeNewGeneration(std::vector<Tree>& trees);
    void breedFitnessBased(int numKids, std::vector<Tree>& newTrees);
    void breedElitismOfSpecies(int numKids, std::vector<Tree>& newTrees);
    void breedChild(Specie& specie, std::vector<Tree>& newTrees);
    void breedElite(std::vector<Specie>& species, std::vector<Tree>& newTrees);

    void crossOver(Tree& child, Tree* n1, Tree* n2);
};

#endif