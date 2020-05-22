
#include "Evolver.h"

#include "Utils.h"


std::vector<Tree> Evolver::makeNewGeneration(std::vector<Tree>& trees) {
    culler.populationSize = (int) trees.size();
    breeder.populationSize = (int) trees.size();

    std::vector<Specie> species = speciator.getSpecies(trees);
    surprise.addSurpriseFitness(trees);
    speciator.sortSpecies(species);

    culler.cullSpecies(species);
    auto singleTrees = culler.selectSingleIDs(species);
    auto pairedTrees = culler.selectPairedIDs(species);

    std::vector<Tree> newTrees = breeder.makeNewGeneration(singleTrees, pairedTrees);

    for (auto& tree : newTrees)
        mutater.mutateTree(tree);
    return newTrees;
}
