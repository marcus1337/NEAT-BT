
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