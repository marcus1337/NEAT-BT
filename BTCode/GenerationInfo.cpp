#include "GenerationInfo.h"

#include <algorithm>
#include <limits>

GenerationInfo::GenerationInfo() {
    averageFitness = 0.f;
    maxFitness = std::numeric_limits<int>::min();
    minFitness = std::numeric_limits<int>::max();
    generation = 0;
    numTrees = 0;
}
void GenerationInfo::saveData(std::ofstream& stream, std::vector<Tree>& trees) {
    storeData(trees);
    stream << maxFitness << '\n';
    stream << minFitness << '\n';
    stream << averageFitness << '\n';
    stream << generation << '\n';
    stream << numTrees << '\n';
    for (int fitness : fitnesses)
        stream << fitness << '\n';
}

void GenerationInfo::storeData(std::vector<Tree>& trees) {
    numTrees = trees.size();
    for (size_t i = 0; i < trees.size(); i++) {
        averageFitness += trees[i].fitness;
        fitnesses.push_back(trees[i].fitness);
        maxFitness = std::max(maxFitness, trees[i].fitness);
        minFitness = std::min(minFitness, trees[i].fitness);
    }
    averageFitness /= trees.size();
}

void GenerationInfo::loadData(std::ifstream& stream) {
    stream >> maxFitness;
    stream >> minFitness;
    stream >> averageFitness;
    stream >> generation;
    stream >> numTrees;
    for (size_t i = 0; i < (size_t) numTrees; i++) {
        int fitness;
        stream >> fitness;
        fitnesses.push_back(fitness);
    }
}