#include <vector>
#include "Tree.h"

#ifndef SPECIE_H
#define SPECIE_H


class Specie {
public:
    int ID;
    int topFitness = 0;
    int averageFitness = 0;

    std::vector<Tree*> trees;
    Tree* getRandomNeat();

    void calcAvgFit();
    Specie();
    Specie(int _id);

    bool operator < (const Specie &right) const;
    bool operator==(const Specie& rhs) const;
};

#endif // !SPECIE_H