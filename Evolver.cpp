
#include "Evolver.h"
#include "Speciator.h"
#include "Culler.h"
#include "Utils.h"
#include "Breeder.h"


std::vector<Tree> Evolver::makeNewGeneration(std::vector<Tree>& trees) {
    Speciator speciator;
    Culler culler;
    Breeder breeder;
    std::vector<Specie> species = speciator.getSpecies(trees);
    culler.cullSpecies(species);
    std::vector<Tree> newTrees = breeder.makeNewGeneration(species, trees.size());
    for (auto& tree : newTrees)
        mutater.mutateTree(tree);
    return newTrees;
}
