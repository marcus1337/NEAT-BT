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
    float getMaxDistance(std::vector<float>& distances);

public:

    float effect = 0.5f;
    void addSurpriseFitness(std::vector<Tree>& trees);
};


#endif