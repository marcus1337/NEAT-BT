#include "Coordinator.h"
#include "IOHandler.h"

using namespace BTE;

void Coordinator::init(int numTrees, int maxOtherInteriorID, int maxUnorderedInteriorID, int maxDecoratorID, int maxActionID, int maxConditionID) {
    Node::maxOtherInteriorID = maxOtherInteriorID;
    Node::maxDecoratorID = maxDecoratorID;
    Node::maxActionID = maxActionID;
    Node::maxConditionID = maxConditionID;
    Node::maxUnorderedInteriorID = maxUnorderedInteriorID;
    trees.resize(numTrees);
}

void Coordinator::saveGeneration(std::string filename) {
    IOHandler iohandler;
    iohandler.saveGeneration(trees, generation, filename);
}

void Coordinator::loadGeneration(std::string filename, int _generation) {
    IOHandler iohandler;
    trees = iohandler.loadGeneration(_generation, filename);
    generation = _generation;
}

char* Coordinator::getTreeString(int index) {
    IOHandler iohandler;
    std::string treeStr = iohandler.getTreeString(trees[index]);
    std::size_t treeCharArraySize = sizeof(treeStringHolder);
    strncpy(treeStringHolder, treeStr.c_str(), treeCharArraySize);
    return &treeStringHolder[0];
}

void Coordinator::evolve() {
    trees = evolver.makeNewGeneration(trees);
    generation++;
}
void Coordinator::setFitness(int index, int fitness) {
    trees[index].fitness = fitness;
}

void Coordinator::setTargetSpecies(int numTargetSpecies) {
    evolver.speciator.targetNumSpecies = std::max(numTargetSpecies,1);
}