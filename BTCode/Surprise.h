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

public:

    void addSurpriseFitness(std::vector<Tree>& trees);
};


#endif