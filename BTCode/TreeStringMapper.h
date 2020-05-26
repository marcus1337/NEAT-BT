

#ifndef TREESTRINGMAPPER_H
#define TREESTRINGMAPPER_H

#include "Tree.h"
#include <tuple>
#include <map>

class TreeStringMapper {
    std::map<std::pair<int, int>, char> charMap;
    bool charMapContains(std::pair<int, int> _key);
    std::string possibleChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
    int freeCharPosition = 0;
    char getChar(int a, int b);
public:

    std::string getMappedTreeString(Tree& tree);

};

#endif
