#include "Speciator.h"

#include <algorithm>
#include "Utils.h"
#include <set>

void Speciator::sortSpecies(std::vector<Specie>& species) {
    for (Specie& spec : species)
        for (const auto& tree : spec.trees)
            spec.topFitness = std::max(spec.topFitness, tree->fitness);
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
    for (size_t i = 0; i < trees.size(); i++)
        adjustFitnessShared(trees, (int) i);
}

void Speciator::adjustFitnessShared(std::vector<Tree>& trees, int index) {
    int divisor = 1;
    for (size_t i = 0; i < trees.size(); i++) {
        if (i != index && sameSpecie(trees[i], trees[index]))
            divisor++;
    }
    trees[index].fitness /= divisor;
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
        int numNeatsInSpecie = (int) species[i].trees.size();
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
        speciateDelta -= speciateDelta / 20;
    if (numSpecies > targetNumSpecies)
        speciateDelta += speciateDelta / 20;
    speciateDelta = (float)((int)(speciateDelta * 10000)) / 10000;
    speciateDelta = std::clamp(speciateDelta, 0.00001f, 1000.0f);
}

float Speciator::nodeTypeDiff(Tree& n1, Tree& n2) {
    std::vector<Node> nodes1 = n1.getNodesCopy();
    std::vector<Node> nodes2 = n2.getNodesCopy();
    int maxSize = (int) std::max(nodes1.size(), nodes2.size());
    int countSame = 0;
    for (const auto& n : nodes1) {
        std::vector<Node>::iterator it = std::find(nodes2.begin(), nodes2.end(), n);
        size_t index = std::distance(nodes2.begin(), it);
        if (index != nodes2.size()) {
            countSame++;
            nodes2.erase(nodes2.begin() + index);
        }
    }
    return (float) countSame / maxSize;
}
float Speciator::treeSizeDiff(Tree& n1, Tree& n2) {
    std::vector<Node> nodes1 = n1.getNodesCopy();
    std::vector<Node> nodes2 = n2.getNodesCopy();
    int maxSize = (int) std::max(nodes1.size(), nodes2.size());
    int minSize = (int) std::min(nodes1.size(), nodes2.size());
    return (float)(maxSize - minSize)/maxSize;
}

std::vector<Specie> Speciator::getSpecies(std::vector<Tree>& trees) {
    std::vector<Specie> species;
    speciate(trees, species);
    return species;
}

bool Speciator::sameSpecie(Tree& n1, Tree& n2) {
    float dd = c1 * nodeTypeDiff(n1, n2);
    float dw = c2 * treeSizeDiff(n1, n2);
    return (dd + dw) < speciateDelta;
}