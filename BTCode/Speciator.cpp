#include "Speciator.h"

#include <algorithm>
#include "Utils.h"
#include <set>
#include <limits>

void Speciator::sortSpecies(std::vector<Specie>& species) {

    for (Specie& spec : species) {
        spec.topFitness = std::numeric_limits<int>::min();
        for (const auto& tree : spec.trees)
            spec.topFitness = std::max(spec.topFitness, tree->fitness);
    }

    std::sort(species.begin(), species.end(), [](const Specie& lhs, const Specie& rhs)
    { return lhs.topFitness > rhs.topFitness; });
    for (Specie& spec : species) {
        sortSpecie(spec);
        spec.calcAvgFit();
    }
}

void Speciator::sortSpecie(Specie& spec) {
    std::sort(spec.trees.begin(), spec.trees.end(), [](const Tree* lhs, const Tree* rhs)
    {
        return lhs->fitness > rhs->fitness;
    });
}

void Speciator::fitnessSharing(std::vector<Tree>& trees) {
    setSharingDivisors(trees);
    for (size_t i = 0; i < trees.size(); i++)
        trees[i].fitness /= sharingDivisors[i];
}

void Speciator::setSharingDivisors(std::vector<Tree>& trees) {
    sharingDivisors = std::vector<int>(trees.size(), 1);
    for (size_t i = 0; i < trees.size(); i++)
        for (size_t j = i; j < trees.size(); j++)
            increaseDivisorsIfSame(trees, i, j);
}

void Speciator::increaseDivisorsIfSame(std::vector<Tree>& trees, int i, int j) {
    if (i != j && sameSpecie(trees[i], trees[j])) {
        sharingDivisors[i]++;
        sharingDivisors[j]++;
    }
}

void Speciator::speciate(std::vector<Tree>& trees, std::vector<Specie>& species) {
    numSpecies = 0;
    for (size_t i = 0; i < trees.size(); i++)
        addToSpecies(trees[i], species);

    fitnessSharing(trees);

    sortSpecies(species);
    adjustDynamicSpecieDelta();
}

void Speciator::addToSpecies(Tree& tree, std::vector<Specie>& species) {
    bool foundSpecies = addToExistingSpecie(tree, species);
    if (!foundSpecies)
        addNewSpecie(tree, species);
}
bool Speciator::addToExistingSpecie(Tree& tree, std::vector<Specie>& species) {
    for (int i = 0; i < numSpecies; i++) {
        int numNeatsInSpecie = (int)species[i].trees.size();
        Tree& tmpNeat = *species[i].trees[Utils::randi(0, numNeatsInSpecie - 1)];
        if (sameSpecie(tree, tmpNeat)) {
            species[i].trees.push_back(&tree);
            return true;
        }
    }
    return false;
}
void Speciator::addNewSpecie(Tree& tree, std::vector<Specie>& species) {
    numSpecies++;
    Specie spec(numSpecies);
    spec.trees.push_back(&tree);
    species.push_back(spec);
}

void Speciator::adjustDynamicSpecieDelta() {
    if (numSpecies < targetNumSpecies)
        speciateDelta--;
    if (numSpecies > targetNumSpecies)
        speciateDelta++;
    speciateDelta = std::clamp(speciateDelta, 1, 10000);
}


std::vector<Specie> Speciator::getSpecies(std::vector<Tree>& trees) {
    setTreeStrings(trees);
    std::vector<Specie> species;
    speciate(trees, species);
    return species;
}

bool Speciator::sameSpecie(Tree& n1, Tree& n2) {

    if (n1.treeStr.size() > 30 || n2.treeStr.size() > 30)
        return true; //hardcoded limitation to prevent freezing

    int editDistance;
    if (speciateDelta < 10)
        editDistance = btDistance.calculateLimitedTreeEditDistance(n1.treeStr, n2.treeStr, speciateDelta);
    else
        editDistance = btDistance.calculateTreeEditDistance(n1.treeStr, n2.treeStr);
    return editDistance < speciateDelta;
}

void Speciator::setTreeStrings(std::vector<Tree>& trees) {
    for (auto& tree : trees) {
        tree.treeStr = treeStringMapper.getMappedTreeString(tree);
    }
}