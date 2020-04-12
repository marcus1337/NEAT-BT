#include <vector>
#include <fstream>
#include "Tree.h"

#ifndef GENERATIONINFO_H
#define GENERATIONINFO_H

class GenerationInfo {

    void storeData(std::vector<Tree>& trees);
public:
    std::vector<int> fitnesses;
    float averageFitness;
    int maxFitness;
    int minFitness;
    int generation;
    int numTrees;

    GenerationInfo();
    void saveData(std::ofstream& stream, std::vector<Tree>& trees);
    void loadData(std::ifstream& stream);
};

#endif