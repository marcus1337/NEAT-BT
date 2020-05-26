#include "Tree.h"
#include <vector>
#include "Specie.h"

#include "TreeStringMapper.h"
#include "../TreeEditDistance/BTDistance.h"

#ifndef SPECIATOR_H
#define SPECIATOR_H

class Speciator {
    void sortSpecie(Specie& spec);
    void fitnessSharing(std::vector<Tree>& trees);
    void setSharingDivisors(std::vector<Tree>& trees);
    std::vector<int> sharingDivisors;
    TreeStringMapper treeStringMapper;
    BTDistance btDistance;

    void setTreeStrings(std::vector<Tree>& trees);

public:

    int targetNumSpecies = 3;
    int speciateDelta = 3;
    void adjustDynamicSpecieDelta();
    int numSpecies = 1;
    std::vector<Specie> getSpecies(std::vector<Tree>& trees);

    bool sameSpecie(Tree& n1, Tree& n2);

    void speciate(std::vector<Tree>& trees, std::vector<Specie>& species);

    void addToSpecies(Tree& tree, std::vector<Specie>& species);
    bool addToExistingSpecie(Tree& tree, std::vector<Specie>& species);
    void addNewSpecie(Tree& tree, std::vector<Specie>& species);

    void sortSpecies(std::vector<Specie>& species);
};

#endif