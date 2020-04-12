#include "Culler.h"

#include <algorithm>

void Culler::removeStaleSpecies(std::vector<Specie>& species) {
    if (species.size() >= numSpeciesLimit)
        species.erase(species.begin() + numSpeciesLimit, species.end());
}

void Culler::cullSpecies(std::vector<Specie>& species) {
    removeStaleSpecies(species);
    removeWeaksInSpecies(species);
    removeWeakSpecies(species);
}

bool Culler::isWeak(const Specie& specie, int numSpecies, int totalAverageFitness) {
    if ((specie.averageFitness > 0 && totalAverageFitness > 0) ||
        (specie.averageFitness < 0 && totalAverageFitness < 0))
        return ((float)specie.averageFitness / totalAverageFitness)*numSpecies < 0.8f;
    return specie.averageFitness < totalAverageFitness;
}

void Culler::removeWeakSpecies(std::vector<Specie>& species) {
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
}

void Culler::cullAllButOneFromSpecies(std::vector<Specie>& species) {
    for (Specie& spec : species) {
        spec.trees = std::vector<Tree*>({ spec.trees[0] });
    }
}

int Culler::getTotalAverageFitness(std::vector<Specie>& species) {
    int total = 0;
    for (const auto& s : species)
        total += s.averageFitness;
    return total;
}