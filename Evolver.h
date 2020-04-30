#include "Tree.h"
#include <vector>
#include "Specie.h"

#include "Mutate.h"
#include "Speciator.h"
#include "Culler.h"
#include "Breeder.h"

#ifndef EVOLVER_H
#define EVOLVER_H

class Evolver {
    Mutate mutater;
    Speciator speciator;
    Culler culler;
    Breeder breeder;
public:
    std::vector<Tree> makeNewGeneration(std::vector<Tree>& trees);

};

#endif