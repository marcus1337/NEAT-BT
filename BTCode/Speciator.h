#include "Tree.h"
#include <vector>
#include "Specie.h"

#ifndef SPECIATOR_H
#define SPECIATOR_H

class Speciator {
    void sortSpecie(Specie& spec);
    void fitnessSharing(std::vector<Tree>& trees);
    void setSharingDivisors(std::vector<Tree>& trees);
    std::vector<int> sharingDivisors;
public:
    static constexpr float c1 = 1.6f;
    static constexpr float c2 = 0.7f;

    int targetNumSpecies = 3;
    float speciateDelta = 3.0f;
    void adjustDynamicSpecieDelta();
    int numSpecies = 1;
    std::vector<Specie> getSpecies(std::vector<Tree>& trees);

    float nodeTypeDiff(Tree& n1, Tree& n2);
    float treeSizeDiff(Tree& n1, Tree& n2);

    bool sameSpecie(Tree& n1, Tree& n2);

    void speciate(std::vector<Tree>& trees, std::vector<Specie>& species);

    void addToSpecies(Tree& tree, std::vector<Specie>& species);
    bool addToExistingSpecie(Tree& tree, std::vector<Specie>& species);
    void addNewSpecie(Tree& tree, std::vector<Specie>& species);

    void sortSpecies(std::vector<Specie>& species);
};

#endif