
#include <vector>
#include "Tree.h"

#ifndef MAPELITES_H
#define MAPELITES_H


class MapElites {
    unsigned char mapOccupied[100][100][100] = {};
    Tree eliteTrees[100][100][100];
public:
    bool isOccupied(int a, int b, int c);
    bool isEliteBetter(int a, int b, int c, Tree& newTree);
    void storeTree(int a, int b, int c, Tree& newTree);
    Tree getTree(int a, int b, int c);
};

#endif // !MAPELITES_H