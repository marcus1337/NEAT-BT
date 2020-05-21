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
    std::vector<float> distances = getDistances(trees);
    float maxDistance = getMaxDistance(distances);
    float totalPot = getTotalPot(trees);

    if (maxDistance <= 0.f || totalPot < 1.f || numGenerations < 5)
        return;

    distributeSurpriseFitness(trees, totalPot, maxDistance, distances);
}

std::vector<float> Surprise::getDistances(std::vector<Tree>& trees) {
    std::vector<float> distances(trees.size());
    for (int i = 0; i < trees.size(); i++)
        distances[i] = mean.distance(trees[i].observedBehaviors);
    return distances;
}

float Surprise::getMaxDistance(std::vector<float>& distances) {
    float maxDistance = std::numeric_limits<float>::min();
    for (int i = 0; i < distances.size(); i++)
        maxDistance = std::fmaxf(distances[i], maxDistance);
    return maxDistance;
}

void Surprise::distributeSurpriseFitness(std::vector<Tree>& trees, float totalPot, float maxDistance,
    std::vector<float>& distances) {

    std::vector<float> normalizedDistances = getNormalizedDistances(distances, maxDistance);
    float maxScore = getMaxScore(totalPot, normalizedDistances);
    for (int i = 0; i < trees.size(); i++)
        trees[i].fitness += (int)(maxScore*normalizedDistances[i]);
}

std::vector<float> Surprise::getNormalizedDistances(std::vector<float>& distances, float maxDistance) {
    std::vector<float> normalizedDistances = distances;
    for (int i = 0; i < distances.size(); i++)
        normalizedDistances[i] /= maxDistance;
    return normalizedDistances;
}

float Surprise::getMaxScore(float totalPot, std::vector<float>& normalizedDistances) {
    float sumNormalizedDistances = std::accumulate(normalizedDistances.begin(), normalizedDistances.end(), 0);
    return totalPot / sumNormalizedDistances;
}

float Surprise::getTotalPot(std::vector<Tree>& trees) {
    float totalPot = 0;
    for (auto& tree : trees) {
        totalPot += tree.fitness*effect;
        tree.fitness -= tree.fitness*effect;
    }
    return totalPot;
}