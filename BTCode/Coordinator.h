
#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "Tree.h"
#include <vector>
#include "Evolver.h"
#include "IOHandler.h"

namespace BTE {
    class Coordinator {
        IOHandler iohandler;
    public:

        std::vector<Tree> trees;
        int generation;
        Evolver evolver;

        void init(int numTrees, int maxOtherInteriorID, int maxUnorderedInteriorID,
            int maxDecoratorID, int maxActionID, int maxConditionID);

        void saveGeneration(std::string filename);
        void loadGeneration(std::string filename, int _generation);
        std::string getTreeString(int index);
        std::string getEliteTreeString(int index);


        void evolve();
        void setFitness(int index, int fitness);
        void setBehavior(int index, std::vector<int> behaviors);
        void setTargetSpecies(int numTargetSpecies);
        void setSurpriseEffect(float effect);

        void randomizePopulation(int minNodes, int maxNodes);
        void randomizePopulationFromElites();

        void mapElites();
        void saveElites(std::string foldername = "TREES_ELITE");
        void loadElites(std::string foldername = "TREES_ELITE");
        void setMaxTreeNodes(int numNodes);
        

    };
}


#endif