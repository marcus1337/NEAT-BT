#include "Tree.h"
#include "Specie.h"
#include <vector>
#include <utility>

#ifndef CULLER_H
#define CULLER_H

class Culler { //rename to Selector
    std::vector<float> getSpecieProbabilities(std::vector<Specie>& oldSpecies);
    std::vector<int> getDiscreteSpecieProbabilities(std::vector<Specie>& oldSpecies);
public:
    int numSpeciesLimit = 200;
    int populationSize = 1;

    int getTotalAverageFitness(std::vector<Specie>& species);

    void removeStaleSpecies(std::vector<Specie>& species);
    void cullSpecies(std::vector<Specie>& species);

    std::vector<Tree*> selectSingleIDs(std::vector<Specie>& species);
    std::vector<std::pair<Tree*, Tree*>> selectPairedIDs(std::vector<Specie>& species);
};

#endif