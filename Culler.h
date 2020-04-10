#include "Tree.h"
#include "Specie.h"
#include <vector>

#ifndef CULLER_H
#define CULLER_H

class Culler {
public:
    int numSpeciesLimit = 200;
    int numSpecies = 1;

    int totalAverageFitness = 1;
    int getTotalAverageFitness(std::vector<Specie>& species);

    void removeStaleSpecies(std::vector<Specie>& species);
    void cullSpecies(std::vector<Specie>& species);
    bool isWeak(const Specie& o);
    void removeWeakSpecies(std::vector<Specie>& species);
    void removeWeaksInSpecies(std::vector<Specie>& species);
    void cullAllButOneFromSpecies(std::vector<Specie>& species);

    int calcNumBreeds(const Specie& specie);
};

#endif