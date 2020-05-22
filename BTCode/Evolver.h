#include "Tree.h"
#include <vector>
#include "Specie.h"

#include "Mutate.h"
#include "Speciator.h"
#include "Selector.h"
#include "Breeder.h"
#include "Surprise.h"

#include "MapElites.h"

#ifndef EVOLVER_H
#define EVOLVER_H

class Evolver {
public:
    Mutate mutater;
    Speciator speciator;
    Selector culler;
    Breeder breeder;
    std::vector<Tree> makeNewGeneration(std::vector<Tree>& trees);

    Surprise surprise;
    MapElites mapElites;
};

#endif