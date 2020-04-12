
#include "Evolver.h"
#include "Speciator.h"
#include "Culler.h"
#include "Utils.h"


std::vector<Tree> Evolver::makeNewGeneration(std::vector<Tree>& trees) {
    std::vector<Tree> result;
    numChildrenLeft = trees.size();
    Speciator speciator;
    Culler culler;
    std::vector<Specie> species = speciator.getSpecies(trees);
    culler.cullSpecies(species);

    breedFitnessBased(numChildrenLeft / 2, trees, species);
    numChildrenLeft -= numChildrenLeft / 2;
    breedElitismOfSpecies(numChildrenLeft, trees, species);

    return result;
}

int Evolver::calcNumBreeds(const Specie& specie, int numSpecies, int totalAverageFitness) {
    return specie.getSpecieStrength(numSpecies, totalAverageFitness)*(specie.trees.size()/2);
}

int Evolver::calcMinNumBreeds(std::vector<Specie>& species, int totalAverageFitness) {
    int maxFound = 0;
    for (const auto& spec : species) {
        maxFound = std::max(calcNumBreeds(spec, species.size(), totalAverageFitness), maxFound);
    }
    if (maxFound <= 0)
        return 1;
    return 0;
}

void Evolver::breedFitnessBased(int numKids, std::vector<Tree>& newTrees, std::vector<Specie>& species) {
    int totalAverageFitness = getTotalAverageFitness(species);
    int minNumBreeds = calcMinNumBreeds(species,totalAverageFitness);
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

void Evolver::breedElitismOfSpecies(int numKids, std::vector<Tree>& newTrees, std::vector<Specie>& species) {
    for (int i = 0; i < numKids; i++)
        breedElite(species, newTrees);
}

void Evolver::breedChild(Specie& specie, std::vector<Tree>& newTrees) {
    Tree* g1 = specie.getRandomTree();
    Tree* g2 = specie.getRandomTree();
    Tree child;
    crossOver(child, g1, g2);
    newTrees.push_back(child);
}

void Evolver::breedElite(std::vector<Specie>& species, std::vector<Tree>& newTrees) {
    int index = Utils::randi(0, species.size() - 1);
    Specie& specie = species[index];
    newTrees.push_back(*specie.trees[0]);
}

void Evolver::crossOver(Tree& child, Tree* n1, Tree* n2) {
    if(n1->fitness < n2->fitness)
        Utils::swapPointers<Tree>(&n1, &n2);
    child = *n1;
    Node* node1 = child.getRandomNode();
    Node* node2 = n2->getRandomNode();
    *node1 = *node2;
}


int Evolver::getTotalAverageFitness(std::vector<Specie>& species) {
    int total = 0;
    for (const auto& s : species)
        total += s.averageFitness;
    return total;
}