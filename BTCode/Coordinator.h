
#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "Tree.h"
#include <vector>
#include "Evolver.h"

namespace BTE {
    class Coordinator {
    public:

        std::vector<Tree> trees;
        char treeStringHolder[10000] = {};
        int generation;
        Evolver evolver;

        void init(int numTrees, int maxOtherInteriorID, int maxUnorderedInteriorID,
            int maxDecoratorID, int maxActionID, int maxConditionID);

        void saveGeneration(std::string filename);
        void loadGeneration(std::string filename, int _generation);
        char* getTreeString(int index);
        void evolve();
        void setFitness(int index, int fitness);
        void setBehavior(int index, std::vector<int> behaviors);
        void setTargetSpecies(int numTargetSpecies);
        void setSurpriseEffect(float effect);

        void randomizePopulation(int minNodes, int maxNodes);
        void randomizePopulationFromElites();

        void mapElites();
        

    };
}


#endif