#include "Culler.h"

#include <algorithm>

void Culler::removeStaleSpecies(std::vector<Specie>& species) {
    int maxSpecies = std::max(populationSize / 2, 1);
    if (species.size() > maxSpecies)
        species.erase(species.begin() + maxSpecies, species.end());
}

void Culler::cullSpecies(std::vector<Specie>& species) {
    removeStaleSpecies(species);
    //removeWeaksInSpecies(species);
    //removeWeakSpecies(species);
}

bool Culler::isWeak(const Specie& specie, int numSpecies, int totalAverageFitness) {
    return specie.getSpecieStrength(numSpecies, totalAverageFitness) < 0.8f;
}

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