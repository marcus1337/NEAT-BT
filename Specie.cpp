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

Tree* Specie::getRandomNeat() {
    if (trees.empty())
        return nullptr;
    int index = Utils::randi(0, trees.size() - 1);
    return trees[index];
}

bool Specie::operator < (const Specie &right) const
{
    return ID < right.ID;
}
bool Specie::operator==(const Specie& rhs) const { return this->ID == rhs.ID; }