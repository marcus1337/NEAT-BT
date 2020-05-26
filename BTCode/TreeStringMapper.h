

#ifndef TREESTRINGMAPPER_H
#define TREESTRINGMAPPER_H

#include "Tree.h"
#include <tuple>
#include <map>
#include <stack>
#include <string>

class TreeStringMapper {
    std::map<std::pair<int, int>, char> charMap;
    bool charMapContains(std::pair<int, int> _key);
    std::string possibleChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
    int freeCharPosition = 0;
    char getChar(int a, int b);

    std::stack<std::pair<Node*, int>> stack;
    std::vector<bool> visitedNodes;
    int orderNum;

    std::string startNewString(Tree& tree);
    void addVisitedNode(std::string& treeStr);
    void addLeafNode(std::string& treeStr, Node* node);
    void addInteriorNode(std::string& treeStr, Node* node, int orderID);
    void addUnvisitedNode(std::string& treeStr, Node* node, int orderID);
public:

    std::string getMappedTreeString(Tree& tree);

};

#endif
