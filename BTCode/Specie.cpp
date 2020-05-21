#include "Specie.h"
#include "Utils.h"

void Specie::calcAvgFit() {

    int total = 0;
    for (const auto& n : trees) {
        total += n->fitness;
    }
    averageFitness = total / trees.size();
}

Specie::Specie() : ID(-1) {}
Specie::Specie(int _id) : ID(_id) {}

Tree* Specie::getRandomTree() {
    if (trees.empty())
        return nullptr;
    int index = Utils::randi(0, trees.size() - 1);
    return trees[index];
}

float Specie::getSpecieStrength(int numSpecies, int totalAverageFitness) const {
    if ((averageFitness > 0 && totalAverageFitness > 0) ||
        (averageFitness < 0 && totalAverageFitness < 0))
        return ((float)averageFitness / totalAverageFitness)*numSpecies;
    if (averageFitness >= totalAverageFitness)
        return 1.f;
    return 0.f;
}

void Specie::setDiscreteProbabilityDistribution() {
    std::vector<float> probabilityDistribution(trees.size());
    int totalFitness = 0;
    for (size_t i = 0; i < trees.size(); i++)
        totalFitness += trees[i]->fitness;
    if (totalFitness <= 0)
    {
        discreteProbabilityDistribution = { 1 };
        return;
    }
    for (size_t i = 0; i < trees.size(); i++)
        probabilityDistribution[i] = ((float)trees[i]->fitness / totalFitness)*1000.f;

    discreteProbabilityDistribution = std::vector<int>(probabilityDistribution.begin(), probabilityDistribution.end());
}

bool Specie::operator < (const Specie &right) const
{
    return ID < right.ID;
}
bool Specie::operator==(const Specie& rhs) const { return this->ID == rhs.ID; }


Specie Specie::getEmptyCopy() {
    Specie result;
    result.ID = ID;
    result.averageFitness = averageFitness;
    result.topFitness = topFitness;
    return result;
}