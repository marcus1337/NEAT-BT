#include "Coordinator.h"
#include "IOHandler.h"
#include <algorithm>

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

void Coordinator::setBehavior(int index, std::vector<int> behaviors) {
    trees[index].observedBehaviors = behaviors;
}

void Coordinator::setSurpriseEffect(float effect) {
    effect = std::clamp(effect, 0.f, 1.f);
    evolver.surprise.effect = effect;
}

void Coordinator::randomizePopulation(int minNodes, int maxNodes) {
    for (size_t i = 0; i < trees.size(); i++) {
        int randNumNodes = Utils::randi(minNodes, maxNodes);
        trees[i] = Tree::makeRandomTree(randNumNodes);
    }
}

void Coordinator::randomizePopulationFromElites() {
    evolver.mapElites.randomElitism(trees);
}

void Coordinator::mapElites() {
    evolver.mapElites.mapOrStoreElites(trees);
}

void Coordinator::saveElites(std::string filename) {
    IOHandler iohandler;
    iohandler.saveElites(evolver.mapElites.eliteTrees);
}

void Coordinator::loadElites(std::string filename) {
    IOHandler iohandler;
    evolver.mapElites.eliteTrees = iohandler.loadElites(filename);
}