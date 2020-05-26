
#include "TreeStringMapper.h"


#include <algorithm>  


bool TreeStringMapper::charMapContains(std::pair<int, int> _key) {
    std::map<std::pair<int, int>, char>::iterator iter = charMap.find(_key);
    if (iter != charMap.end())
        return true;
    return false;
}

char TreeStringMapper::getChar(int a, int b) {
    auto _key = std::make_pair(a, b);
    if (charMapContains(_key))
        return charMap[_key];
    char newChar = possibleChars[freeCharPosition];
    charMap[_key] = newChar;
    freeCharPosition++;
    return newChar;
}

std::string TreeStringMapper::startNewString(Tree& tree) {
    stack = std::stack<std::pair<Node*, int>>();
    visitedNodes = std::vector<bool>(tree.getNumberOfNodes(), false);
    orderNum = 0;
    stack.push(std::make_pair(&tree.root, orderNum++));
    return "{";
}

void TreeStringMapper::addVisitedNode(std::string& treeStr) {
    treeStr += "}";
}

void TreeStringMapper::addLeafNode(std::string& treeStr, Node* node) {
    treeStr += std::string("{") + getChar(node->type, node->ID) + "}";
}

void TreeStringMapper::addInteriorNode(std::string& treeStr, Node* node, int orderID) {
    stack.push(std::make_pair(node, orderID));
    treeStr += getChar(node->type, node->ID);
    treeStr += '{';
    if (node->type == UNORDERED_INTERIOR)
        std::sort(node->children.begin(), node->children.end());
    for (auto& n : node->children) {
        stack.push(std::make_pair(&n, orderNum++));
    }
}

void TreeStringMapper::addUnvisitedNode(std::string& treeStr, Node* node, int orderID) {
    if (!node->isParent())
        addLeafNode(treeStr, node);
    else
        addInteriorNode(treeStr, node, orderID);
}

std::string TreeStringMapper::getMappedTreeString(Tree& tree) {

    std::string treeStr = startNewString(tree);

    while (!stack.empty()) {
        auto stackElement = stack.top();
        auto node = stackElement.first;
        int orderID = stackElement.second;
        stack.pop();

        if (visitedNodes[orderID])
            addVisitedNode(treeStr);
        else
            addUnvisitedNode(treeStr, node, orderID);

        visitedNodes[orderID] = true;
    }


    treeStr += "}";
    return treeStr;
}