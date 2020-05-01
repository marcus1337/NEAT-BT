#include "Culler.h"
#include <functional> 
#include <algorithm>
#include "Utils.h"

void Culler::removeStaleSpecies(std::vector<Specie>& species) {
    int maxSpecies = std::max(populationSize / 2, 1);
    if (species.size() > maxSpecies)
        species.erase(species.begin() + maxSpecies, species.end());
}

void Culler::cullSpecies(std::vector<Specie>& species) {
    removeStaleSpecies(species);
}

std::vector<int> Culler::getDiscreteSpecieProbabilities(std::vector<Specie>& species) {
    std::vector<float> specieProbabilities = getSpecieProbabilities(species);
    std::transform(specieProbabilities.begin(), specieProbabilities.end(), specieProbabilities.begin(),
        std::bind(std::multiplies<>(), std::placeholders::_1, 1000));
    return std::vector<int>(specieProbabilities.begin(), specieProbabilities.end());
}

std::vector<Tree*> Culler::selectSingleIDs(std::vector<Specie>& species) {
    std::vector<int> specieProbabilities = getDiscreteSpecieProbabilities(species);
    for (auto& specie : species)
        specie.setDiscreteProbabilityDistribution();

    std::vector<Tree*> result;
    for (int i = 0; i < populationSize; i++) {
        int randSpecie = Utils::randIndex(specieProbabilities);
        int randSpecieIndex = Utils::randIndex(species[randSpecie].discreteProbabilityDistribution);
        result.push_back(species[randSpecie].trees[randSpecieIndex]);
    }

    return result;
}

std::vector<std::pair<Tree*, Tree*>> Culler::selectPairedIDs(std::vector<Specie>& species) {
    std::vector<int> specieProbabilities = getDiscreteSpecieProbabilities(species);
    for (auto& specie : species)
        specie.setDiscreteProbabilityDistribution();
    
    std::vector<std::pair<Tree*, Tree*>> result;
    for (int i = 0; i < populationSize; i++) {
        int randSpecie = Utils::randIndex(specieProbabilities);
        int randSpecieIndex1 = Utils::randIndex(species[randSpecie].discreteProbabilityDistribution);
        int randSpecieIndex2 = Utils::randIndex(species[randSpecie].discreteProbabilityDistribution);
        std::pair<Tree*, Tree*> crossPair;
        crossPair.first = species[randSpecie].trees[randSpecieIndex1];
        crossPair.second = species[randSpecie].trees[randSpecieIndex2];
        result.push_back(crossPair);
    }
    return result;
}

std::vector<float> Culler::getSpecieProbabilities(std::vector<Specie>& oldSpecies) {
    std::vector<float> specieProbabilities;
    int totalAverageFitness = getTotalAverageFitness(oldSpecies);
    if (totalAverageFitness <= 0)
        return std::vector<float>(oldSpecies.size(), 1.f);
    else {
        for (int i = 0; i < oldSpecies.size(); i++) {
            float speciesProbability = std::max<float>((float)oldSpecies[i].averageFitness / totalAverageFitness, 0);
            specieProbabilities.push_back(speciesProbability);
        }
    }
    return specieProbabilities;
}

/*bool Culler::isWeak(const Specie& specie, int numSpecies, int totalAverageFitness) {
    return specie.getSpecieStrength(numSpecies, totalAverageFitness) < 0.8f;
}*/

/*void Culler::removeWeakSpecies(std::vector<Specie>& species) {
    int numSpecies = species.size();
    int totalAverageFitness = getTotalAverageFitness(species);
    species.erase(std::remove_if(species.begin(), species.end(),
        [&](const Specie& o) { return isWeak(o, numSpecies, totalAverageFitness); }), species.end());
}
void Culler::removeWeaksInSpecies(std::vector<Specie>& species) {
    for (Specie& spec : species) {
        std::vector<Tree*> survivors;
        int remaining = spec.trees.size() / 2;
        if (remaining == 0)
            survivors.push_back(spec.trees[0]);
        for (int i = 0; i < remaining; i++)
            survivors.push_back(spec.trees[i]);
        spec.trees = survivors;
    }
    species.erase(std::remove_if(species.begin(), species.end(),
        [](const Specie& o) { return o.trees.size() == 0; }), species.end());
}*/

/*void Culler::cullAllButOneFromSpecies(std::vector<Specie>& species) {
    for (Specie& spec : species) {
        spec.trees = std::vector<Tree*>({ spec.trees[0] });
    }
}*/

int Culler::getTotalAverageFitness(std::vector<Specie>& species) {
    int total = 0;
    for (const auto& s : species)
        total += s.averageFitness;
    return total;
}