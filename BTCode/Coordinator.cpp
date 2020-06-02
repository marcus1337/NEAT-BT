#include "Coordinator.h"
#include <algorithm>

using namespace BTE;

void Coordinator::init(int numTrees, int maxOtherInteriorID, int maxUnorderedInteriorID, int maxDecoratorID, int maxActionID, int maxConditionID) {
    Node::maxOtherInteriorID = maxOtherInteriorID;
    Node::maxDecoratorID = maxDecoratorID;
    Node::maxActionID = maxActionID;
    Node::maxConditionID = maxConditionID;
    Node::maxUnorderedInteriorID = maxUnorderedInteriorID;
    generation = 1;
    trees.resize(numTrees);
}

void Coordinator::saveGeneration(std::string filename) {
    iohandler.saveGeneration(trees, generation, filename);
}

void Coordinator::loadGeneration(std::string filename, int _generation) {
    trees = iohandler.loadGeneration(_generation, filename);
    generation = _generation;
}

std::string Coordinator::getTreeString(int index) {
    return iohandler.getTreeString(trees[index]);
}

std::string Coordinator::getEliteTreeString(int index) {
    auto allElites = evolver.mapElites.getElitesVector();
    return iohandler.getTreeString(allElites[index]);
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

void Coordinator::saveElites(std::string foldername) {
    iohandler.saveElites(evolver.mapElites.eliteTrees, foldername);
}

void Coordinator::loadElites(std::string foldername) {
    evolver.mapElites.eliteTrees = iohandler.loadElites(foldername);
}

void Coordinator::setMaxTreeNodes(int numNodes) {
    evolver.mutater.maxTreeNodes = numNodes;
}