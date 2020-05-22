
#include "MapElites.h"

bool MapElites::isOccupied(int a, int b, int c) {
    return mapOccupied[a][b][c] != 0;
}

bool MapElites::isEliteBetter(int a, int b, int c, Tree& newTree) {
    return isOccupied(a, b, c) && eliteTrees[a][b][c].fitness > newTree.fitness;
}

void MapElites::storeTree(int a, int b, int c, Tree& newTree) {
    eliteTrees[a][b][c] = newTree;
}

Tree MapElites::getTree(int a, int b, int c) {
    return eliteTrees[a][b][c];
}

void MapElites::mapOrStoreElite(Tree& oldTree) {
    int a = oldTree.observedBehaviors[0];
    int b = oldTree.observedBehaviors[1];
    int c = oldTree.observedBehaviors[2];
    if (!isOccupied(a, b, c) || eliteTrees[a][b][c].fitness < oldTree.fitness) {
        mapOccupied[a][b][c] = 1;
        eliteTrees[a][b][c] = oldTree;
    }
    else
        oldTree = eliteTrees[a][b][c];
}

void MapElites::mapOrStoreElites(std::vector<Tree>& trees) {
    for (size_t i = 0; i < trees.size(); i++)
        mapOrStoreElite(trees[i]);
}