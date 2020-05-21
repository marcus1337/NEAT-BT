#include <vector>
#include "Tree.h"


#ifndef SURPRISE_H
#define SURPRISE_H

class Surprise {
    int numElements = -1;
    int numTrees = -1;
    int numGenerations;
    void initMean(std::vector<Tree>& trees);
    void updateMean(std::vector<Tree>& trees);
    std::vector<double> getMean(std::vector<Tree>& trees);
    std::vector<double> mean;

    std::vector<double> subVectors(std::vector<double> a, std::vector<double> b);
    std::vector<double> addVectors(std::vector<double> a, std::vector<double> b);
    std::vector<double> divVectors(std::vector<double> a, int divisor);

public:

    void addSurpriseFitness(std::vector<Tree>& trees);
};


#endif