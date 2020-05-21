#include "Surprise.h"
#include <limits>

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
    updateMean(trees);
    if (numGenerations < 5)
        return;

    std::vector<float> distances(trees.size());
    float maxDistance = std::numeric_limits<float>::min();
    for (int i = 0; i < trees.size(); i++) {
        distances[i] = mean.distance(trees[i].observedBehaviors);
        maxDistance = std::fmaxf(distances[i], maxDistance);
    }

    if (maxDistance == 0.f)
        return;

    float sumDistances = std::accumulate(distances.begin(), distances.end(), 0);

    float totalPot = 0;
    for (auto& tree : trees) {
        totalPot += tree.fitness*effect;
        tree.fitness -= tree.fitness*effect;
    }
    
}