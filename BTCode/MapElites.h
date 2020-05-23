
#include <vector>
#include "Tree.h"

#include <map>
#include <algorithm>
#include <vector>
#include <tuple>

#ifndef MAPELITES_H
#define MAPELITES_H


class MapElites {

    std::map<std::tuple<int,int,int>,Tree> eliteTrees;

public:
    MapElites();

    bool isOccupied(int a, int b, int c);
    bool isEliteBetter(int a, int b, int c, Tree& newTree);
    void storeTree(int a, int b, int c, Tree& newTree);
    Tree getTree(int a, int b, int c);

    void mapOrStoreElite(Tree& oldTree);
    void mapOrStoreElites(std::vector<Tree>& trees);
    bool isNewTreeBetter(std::tuple<int, int, int> key, Tree& newTree);
};

#endif // !MAPELITES_H