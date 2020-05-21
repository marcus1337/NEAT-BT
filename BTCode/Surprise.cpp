#include "Surprise.h"

void Surprise::initMean(std::vector<Tree>& trees) {
    numElements = trees[0].observedBehaviors.size();
    numTrees = trees.size();
    mean = getMean(trees);
    numGenerations = 1;
}

Behavior<float> Surprise::getMean(std::vector<Tree>& trees) {
    Behavior<float> result;
    for (const auto& tree : trees)
        result += tree.observedBehaviors;
    result /= numTrees;
    return result;
}

void Surprise::updateMean(std::vector<Tree>& trees) {
    if (mean.empty())
        initMean(trees);

    Behavior<float> latestMean = getMean(trees);
    mean += (latestMean - mean) / numGenerations;
    numGenerations++;
}

void Surprise::addSurpriseFitness(std::vector<Tree>& trees) {

}