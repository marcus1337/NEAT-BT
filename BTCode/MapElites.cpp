
#include "MapElites.h"
#include <functional>
#include <iterator> 
#include "Utils.h"

MapElites::MapElites() {

}

bool MapElites::isOccupied(std::tuple<int, int, int> key) {
    std::map<std::tuple<int, int, int>, Tree>::iterator it = eliteTrees.find(key);
    if (it != eliteTrees.end())
        return true;
    return false;
}

bool MapElites::isOccupied(int a, int b, int c) {
    std::map<std::tuple<int, int, int>, Tree>::iterator it = eliteTrees.find(std::make_tuple(a, b, c));
    if (it != eliteTrees.end())
        return true;
    return false;
}

bool MapElites::isEliteBetter(int a, int b, int c, Tree& tree) {
    return isOccupied(a, b, c) && eliteTrees[getKey(tree)].fitness > tree.fitness;
}

void MapElites::storeTree(int a, int b, int c, Tree& newTree) {
    eliteTrees[std::make_tuple(a, b, c)] = newTree;
}

Tree MapElites::getTree(int a, int b, int c) {
    return eliteTrees[std::make_tuple(a, b, c)];
}

void MapElites::mapOrStoreElite(Tree& tree) {
    auto _key = getKey(tree);
    if (!isOccupied(_key) || isNewTreeBetter(_key, tree))
        eliteTrees[_key] = tree;
    else
        tree = eliteTrees[_key];
}

bool MapElites::isNewTreeBetter(std::tuple<int, int, int> _key, Tree& tree) {
    return eliteTrees[_key].fitness < tree.fitness
        || (eliteTrees[_key].fitness == tree.fitness &&
            eliteTrees[_key].getNumberOfNodes() > tree.getNumberOfNodes());
}

void MapElites::mapOrStoreElites(std::vector<Tree>& trees) {
    for (size_t i = 0; i < trees.size(); i++)
        mapOrStoreElite(trees[i]);
}

void MapElites::storeElite(Tree& tree) {
    auto _key = getKey(tree);
    if (!isOccupied(_key) || isNewTreeBetter(_key, tree))
        eliteTrees[_key] = tree;
}
void MapElites::storeElites(std::vector<Tree>& trees) {
    for (size_t i = 0; i < trees.size(); i++)
        storeElite(trees[i]);
}

void MapElites::randomElitism(std::vector<Tree>& trees) {
    std::vector<Tree> allElites;
    std::transform(eliteTrees.begin(),eliteTrees.end(),std::back_inserter(allElites),
        [](auto &kv) { return kv.second; });
    for (size_t i = 0; i < trees.size(); i++) {
        int randomEliteIndex = Utils::randi(0, allElites.size() - 1);
        trees[i] = allElites[randomEliteIndex];
    }
}

std::tuple<int, int, int> MapElites::getKey(Tree& tree) {
    int a = tree.observedBehaviors[0];
    int b = tree.observedBehaviors[1];
    int c = tree.observedBehaviors[2];
    return std::make_tuple(a, b, c);
}