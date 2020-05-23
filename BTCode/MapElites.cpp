
#include "MapElites.h"
#include <functional>

MapElites::MapElites() {

}

bool MapElites::isOccupied(int a, int b, int c) {
    std::map<std::tuple<int, int, int>, Tree>::iterator it = eliteTrees.find(std::make_tuple(a, b, c));
    if (it != eliteTrees.end())
        return true;
    return false;
}

bool MapElites::isEliteBetter(int a, int b, int c, Tree& newTree) {
    return isOccupied(a, b, c) && eliteTrees[std::make_tuple(a, b, c)].fitness > newTree.fitness;
}

void MapElites::storeTree(int a, int b, int c, Tree& newTree) {
    eliteTrees[std::make_tuple(a, b, c)] = newTree;
}

Tree MapElites::getTree(int a, int b, int c) {
    return eliteTrees[std::make_tuple(a, b, c)];
}

void MapElites::mapOrStoreElite(Tree& newTree) {
    int a = newTree.observedBehaviors[0];
    int b = newTree.observedBehaviors[1];
    int c = newTree.observedBehaviors[2];
    auto _key = std::make_tuple(a, b, c);

    if (!isOccupied(a, b, c) || eliteTrees[_key].fitness < newTree.fitness)
        eliteTrees[_key] = newTree;
    else
        newTree = eliteTrees[_key];
}

void MapElites::mapOrStoreElites(std::vector<Tree>& trees) {
    for (size_t i = 0; i < trees.size(); i++)
        mapOrStoreElite(trees[i]);
}