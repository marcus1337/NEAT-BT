#include "Breeder.h"
#include "Utils.h"
#include <algorithm>

std::vector<Tree> Breeder::makeNewGeneration(std::vector<Specie>& species, int totalNumTrees) {
    std::vector<Tree> trees;
    numChildrenLeft = totalNumTrees;

    breedFitnessBased(numChildrenLeft / 2, trees, species);
    numChildrenLeft -= numChildrenLeft / 2;
    breedElitismOfSpecies(numChildrenLeft, trees, species);

    removeInvalidAndAddRemaining(trees, species, totalNumTrees);
    return trees;
}

void Breeder::removeInvalidAndAddRemaining(std::vector<Tree>& newTrees,
    std::vector<Specie>& species, int targetGenerationSize) {
    removeTreesWithoutActionNodes(newTrees);
    breedElitismOfSpecies(targetGenerationSize - newTrees.size(), newTrees, species);
}

void Breeder::removeTreesWithoutActionNodes(std::vector<Tree>& newTrees) {
    newTrees.erase(std::remove_if(
        newTrees.begin(), newTrees.end(),
        [](Tree& x) {return x.getNumberOfNodesOfType(ACTION) == 0; }), newTrees.end());
}

int Breeder::calcNumBreeds(const Specie& specie, int numSpecies, int totalAverageFitness) {
    return specie.getSpecieStrength(numSpecies, totalAverageFitness)*(specie.trees.size() / 2);
}

int Breeder::calcMinNumBreeds(std::vector<Specie>& species, int totalAverageFitness) {
    int maxFound = 0;
    for (const auto& spec : species) {
        maxFound = std::max(calcNumBreeds(spec, species.size(), totalAverageFitness), maxFound);
    }
    if (maxFound <= 0)
        return 1;
    return 0;
}

void Breeder::breedFitnessBased(int numKids, std::vector<Tree>& newTrees, std::vector<Specie>& species) {
    int totalAverageFitness = getTotalAverageFitness(species);
    int minNumBreeds = calcMinNumBreeds(species, totalAverageFitness);
    while (numKids > 0) {
        for (Specie& spec : species) {
            int numBreeds = std::max(calcNumBreeds(spec, species.size(), totalAverageFitness), minNumBreeds);
            for (int i = 0; i < numBreeds && numKids > 0; i++) {
                breedChild(spec, newTrees);
                numKids--;
            }
        }
    }
}

void Breeder::breedElitismOfSpecies(int numKids, std::vector<Tree>& newTrees, std::vector<Specie>& species) {
    for (int i = 0; i < numKids; i++)
        breedElite(species, newTrees);
}

void Breeder::breedChild(Specie& specie, std::vector<Tree>& newTrees) {
    Tree* g1 = specie.getRandomTree();
    Tree* g2 = specie.getRandomTree();
    Tree child;
    crossOver(child, g1, g2);
    newTrees.push_back(child);
}

void Breeder::breedElite(std::vector<Specie>& species, std::vector<Tree>& newTrees) {
    int index = Utils::randi(0, species.size() - 1);
    Specie& specie = species[index];
    newTrees.push_back(*specie.trees[0]);
}

void Breeder::crossOver(Tree& child, Tree* n1, Tree* n2) {
    if (n1->fitness < n2->fitness)
        Utils::swapPointers<Tree>(&n1, &n2);
    child = *n1;
    Node* node1 = child.getRandomNode();
    Node* node2 = n2->getRandomNode();
    *node1 = *node2;
}


int Breeder::getTotalAverageFitness(std::vector<Specie>& species) {
    int total = 0;
    for (const auto& s : species)
        total += s.averageFitness;
    return total;
}