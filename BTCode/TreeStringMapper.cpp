
#include "TreeStringMapper.h"

#include <stack>
#include <algorithm>  
#include <string>

#include <iostream>
using namespace std;

bool TreeStringMapper::charMapContains(std::pair<int, int> _key) {
    std::map<std::pair<int, int>, char>::iterator iter = charMap.find(_key);
    if (iter != charMap.end())
        return true;
    return false;
}

char TreeStringMapper::getChar(int a, int b) {
    auto _key = std::make_pair(a, b);
    if(charMapContains(_key))
        return charMap[_key];
    char newChar = possibleChars[freeCharPosition];
    charMap[_key] = newChar;
    freeCharPosition++;
    return newChar;
}

std::string TreeStringMapper::getMappedTreeString(Tree& tree) {

    std::stack<std::pair<Node*,int>> stack;
    std::vector<bool> visitedNodes(tree.getNumberOfNodes()+10, false);

    int orderNum = 0;
    stack.push(std::make_pair(&tree.root, orderNum++));

    std::string strTree = "{";

    int interiorIndex = 0;

    while (!stack.empty()) {
        auto stackElement = stack.top();
        auto node = stackElement.first;
        int orderID = stackElement.second;
        stack.pop();

        if (visitedNodes[orderID]) {
            strTree += "}";
        }
        else {
            if (!node->isParent()) {
                strTree += std::string("{") + getChar(node->type, node->ID) + "}";
            }
            else {
                stack.push(std::make_pair(node, orderID));

                strTree += getChar(tree.root.type, tree.root.ID);
                strTree += '{';
                if (node->type == UNORDERED_INTERIOR)
                    std::sort(node->children.begin(), node->children.end());
                for (auto& n : node->children) {
                    stack.push(std::make_pair(&n, ++orderNum));
                }
                   
            }
        }
   
        visitedNodes[orderID] = true;
    }


    strTree += "}";
    return strTree;
}