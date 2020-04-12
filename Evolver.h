#include "Tree.h"
#include <vector>
#include "Specie.h"
#include "Mutate.h"

#ifndef EVOLVER_H
#define EVOLVER_H

class Evolver {
    Mutate mutater;
public:
    std::vector<Tree> makeNewGeneration(std::vector<Tree>& trees);

};

#endif