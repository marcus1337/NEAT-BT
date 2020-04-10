
#include "Evolver.h"
#include "Speciator.h"
#include "Culler.h"


std::vector<Tree> Evolver::makeNewGeneration(std::vector<Tree>& trees) {
    std::vector<Tree> result;
    numChildrenLeft = trees.size();
    Speciator speciator;
    Culler culler;
    std::vector<Specie> species = speciator.getSpecies(trees);
    culler.cullSpecies(species);

    breedFitnessBased(numChildrenLeft / 2, trees);
    numChildrenLeft -= numChildrenLeft / 2;
    breedElitismOfSpecies(numChildrenLeft, trees);

    return result;
}

void Evolver::breedFitnessBased(int numKids, std::vector<Tree>& newTrees) {

}

void Evolver::breedElitismOfSpecies(int numKids, std::vector<Tree>& newTrees) {

}

void Evolver::breedChild(Specie& specie, std::vector<Tree>& newTrees) {

}
