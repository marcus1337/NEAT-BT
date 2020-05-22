#include "Surprise.h"
#include <limits>

void Surprise::initMean(std::vector<Tree>& trees) {
    numElements = (int) trees[0].observedBehaviors.size();
    numTrees = (int) trees.size();
    mean = getMean(trees);
    numGenerations = 1;
}

Behavior<float> Surprise::getMean(std::vector<Tree>& trees) {
    Behavior<float> result;
    result.set({ 0,0,0 });
    for (const auto& tree : trees)
        result += tree.observedBehaviors;
    result /= numTrees;
    return result;
}

void Surprise::updateMean(std::vector<Tree>& trees) {
    if (mean.empty() || numGenerations > 10)
        initMean(trees);

    Behavior<float> latestMean = getMean(trees);
    mean += (latestMean - mean) / numGenerations;
    numGenerations++;
}

bool Surprise::shouldSurprise(float maxDistance, float totalPot) {
    if (maxDistance <= 0.5f || totalPot < 1.f || effect <= 0.0001f)
        return false;
    return true;
}

void Surprise::addSurpriseFitness(std::vector<Tree>& trees) {
    updateMean(trees);

    std::vector<float> distances = getDistances(trees);
    float maxDistance = getMaxDistance(distances);
    float totalPot = getTotalPot(trees);

    if(!shouldSurprise(maxDistance, totalPot))
        return;

    removeFitness(trees);
    distributeSurpriseFitness(trees, totalPot, maxDistance, distances);
}

void Surprise::removeFitness(std::vector<Tree>& trees) {
    for (auto& tree : trees)
        tree.fitness -= (int)((float)tree.fitness*effect);
}

std::vector<float> Surprise::getDistances(std::vector<Tree>& trees) {
    std::vector<float> distances(trees.size());
    for (size_t i = 0; i < trees.size(); i++)
        distances[i] = mean.distance(trees[i].observedBehaviors);
    return distances;
}

float Surprise::getMaxDistance(std::vector<float>& distances) {
    float maxDistance = std::numeric_limits<float>::min();
    for (size_t i = 0; i < distances.size(); i++)
        maxDistance = std::fmaxf(distances[i], maxDistance);
    return maxDistance;
}

void Surprise::distributeSurpriseFitness(std::vector<Tree>& trees, float totalPot, float maxDistance,
    std::vector<float>& distances) {

    std::vector<float> normalizedDistances = getNormalizedDistances(distances, maxDistance);
    float maxScore = getMaxScore(totalPot, normalizedDistances);
    for (size_t i = 0; i < trees.size(); i++) {
        trees[i].fitness += (int)(maxScore*normalizedDistances[i]);
    }
}

std::vector<float> Surprise::getNormalizedDistances(std::vector<float>& distances, float maxDistance) {
    std::vector<float> normalizedDistances = distances;
    for (size_t i = 0; i < distances.size(); i++)
        normalizedDistances[i] /= maxDistance;
    return normalizedDistances;
}

float Surprise::getMaxScore(float totalPot, std::vector<float>& normalizedDistances) {
    float sumNormalizedDistances = std::accumulate(normalizedDistances.begin(), normalizedDistances.end(), 0.f);
    return totalPot / sumNormalizedDistances;
}

float Surprise::getTotalPot(std::vector<Tree>& trees) {
    float totalPot = 0;
    for (auto& tree : trees)
        totalPot += tree.fitness*effect;
    return totalPot;
}