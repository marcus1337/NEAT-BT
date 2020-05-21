#include "Surprise.h"

void Surprise::initMean(std::vector<Tree>& trees) {
    numElements = trees[0].observedBehaviors.size();
    numTrees = trees.size();
    mean = getMean(trees);
    numGenerations = 1;
}

std::vector<double> Surprise::getMean(std::vector<Tree>& trees) {
    std::vector<double> result(numElements, 0);
    for (const auto& tree : trees) {
        for (int i = 0; i < numElements; i++) {
            result[i] += tree.observedBehaviors[i];
        }
    }
    for (int i = 0; i < numElements; i++)
        result[i] *= 1.0 / numTrees;
    return result;
}

void Surprise::updateMean(std::vector<Tree>& trees) {
    if (mean.empty()) {
        initMean(trees);
        return;
    }


    std::vector<double> latestMean = getMean(trees);
    //mean = mean + (latestMean - mean) / numGenerations;
    numGenerations++;
}

void Surprise::addSurpriseFitness(std::vector<Tree>& trees) {

}