#include "Tree.h"
#include <vector>
#include "Specie.h"

#ifndef BREEDER_H
#define BREEDER_H

class Breeder {
    int numChildrenLeft = 0;
    void crossOver(Tree& child, Tree* n1, Tree* n2);
    int getTotalAverageFitness(std::vector<Specie>& species);
    int calcNumBreeds(const Specie& o, int numSpecies, int totalAverageFitness);
    int calcMinNumBreeds(std::vector<Specie>& species, int totalAverageFitness);
    void removeTreesWithoutActionNodes(std::vector<Tree>& newTrees);
    void removeInvalidAndAddRemaining(std::vector<Tree>& newTrees, 
        std::vector<Specie>& species, int targetGenerationSize);

public:
    std::vector<Tree> makeNewGeneration(std::vector<Specie>& species, int totalNumTrees);

    void breedFitnessBased(int numKids, std::vector<Tree>& newTrees, std::vector<Specie>& species);
    void breedElitismOfSpecies(int numKids, std::vector<Tree>& newTrees, std::vector<Specie>& species);
    void breedChild(Specie& specie, std::vector<Tree>& newTrees);
    void breedElite(std::vector<Specie>& species, std::vector<Tree>& newTrees);

};

#endif // !BREEDER_H