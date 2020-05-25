#include "Tree.h"
#include <vector>

#ifndef MUTATIONRATECONTROL_H
#define MUTATIONRATECONTROL_H


class MutationRateControl {

    int numEvaluatedGenerations = 1;
    int numSuccesfulGenerations = 0;
    int priorBestFitness = 0;
    int currentBestFitness = 0;
    bool shouldIncreaseMutationRate();
    bool shouldDecreaseMutationRate();

public:

    void modifyMutationRate(float& mutationChance, std::vector<Tree>& trees);
};


#endif // !MUTATIONRATECONTRO_H