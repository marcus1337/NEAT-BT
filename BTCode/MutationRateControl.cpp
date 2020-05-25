#include "MutationRateControl.h"
#include <algorithm>

bool MutationRateControl::shouldIncreaseMutationRate() {
    return numSuccesfulGenerations > 1;
}
bool MutationRateControl::shouldDecreaseMutationRate() {
    return numSuccesfulGenerations < 1;
}


void MutationRateControl::modifyMutationRate(float& mutationChance, std::vector<Tree>& trees) {
    for (const auto& tree : trees)
        currentBestFitness = std::max(currentBestFitness, tree.fitness);

    if (currentBestFitness > priorBestFitness)
        numSuccesfulGenerations++;

    if (numEvaluatedGenerations == 0) {
        if (shouldIncreaseMutationRate())
            mutationChance *= 2.0f;
        if (shouldDecreaseMutationRate())
            mutationChance /= 2.0f;
        mutationChance = std::clamp(mutationChance, 0.01f, 0.5f);
        numSuccesfulGenerations = 0;
    }

    priorBestFitness = currentBestFitness;
    numEvaluatedGenerations = (numEvaluatedGenerations + 1) % 5;
}