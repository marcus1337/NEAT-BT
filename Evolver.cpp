
#include "Evolver.h"

#include "Utils.h"


std::vector<Tree> Evolver::makeNewGeneration(std::vector<Tree>& trees) {
    culler.populationSize = trees.size();

    std::vector<Specie> species = speciator.getSpecies(trees);
    culler.cullSpecies(species);
    std::vector<Tree> newTrees = breeder.makeNewGeneration(species, trees.size());
    for (auto& tree : newTrees)
        mutater.mutateTree(tree);
    return newTrees;
}
