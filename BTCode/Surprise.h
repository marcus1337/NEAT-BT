#include <vector>
#include "Tree.h"
#include "Behavior.h"

#ifndef SURPRISE_H
#define SURPRISE_H

class Surprise {
    int numElements = -1;
    int numTrees = -1;
    int numGenerations;
    void initMean(std::vector<Tree>& trees);
    void updateMean(std::vector<Tree>& trees);
    Behavior<float> getMean(std::vector<Tree>& trees);
    Behavior<float> mean;
    float getTotalPot(std::vector<Tree>& trees);
    void distributeSurpriseFitness(std::vector<Tree>& trees, float totalPot, float maxDistance,
        std::vector<float>& distances);
    std::vector<float> getDistances(std::vector<Tree>& trees);
    std::vector<float> getNormalizedDistances(std::vector<float>& distances, float maxDistance);
    float getMaxDistance(std::vector<float>& distances);
    float getMaxScore(float totalPot, std::vector<float>& normalizedDistances);
    void removeFitness(std::vector<Tree>& trees);

    bool shouldSurprise(float maxDistance, float totalPot);
public:

    float effect = 0.5f;
    void addSurpriseFitness(std::vector<Tree>& trees);
};


#endif