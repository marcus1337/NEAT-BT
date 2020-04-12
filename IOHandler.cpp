#include "IOHandler.h"
#include <filesystem>
#include <iostream>
#include <stack>

namespace fs = std::filesystem;

std::string IOHandler::getPath(std::string fileName) {
    std::string filePath = std::filesystem::current_path().string();
    filePath += "\\" + fileName;
    return filePath;
}

void IOHandler::makeFolder(std::string folderName) {
    fs::create_directory(getPath(folderName));
}

std::string IOHandler::getFolderName(int generation, std::string folderName) {
    return std::string(folderName + "_" + std::to_string(generation));
}

std::string IOHandler::getFilenameWithPath(std::string folderNameAndGeneration, int treeIndex) {
    return getPath(std::string(folderNameAndGeneration + "//TREE_" + std::to_string(treeIndex)+ ".txt"));
}

std::ofstream IOHandler::getFileStream(int treeIndex, int generation, std::string folderName) {
    std::string folderNameAndGeneration = getFolderName(generation, folderName);
    makeFolder(folderNameAndGeneration);
    return std::ofstream(getFilenameWithPath(folderNameAndGeneration, treeIndex));
}

std::string IOHandler::getParentNodeString(Node* node) {
    std::string res;
    res += parentStartTag + std::string(" " + std::to_string(node->type) + " " + std::to_string(node->ID)) + '\n';
    for (auto& n : node->children)
        res += std::string(std::to_string(n.type) + " " + std::to_string(n.ID)) + '\n';
    res += parentEndTag + '\n';
    return res;
}

void IOHandler::saveTree(Tree& tree, int treeIndex, int generation, std::string folderName) {
    std::ofstream stream = getFileStream(treeIndex, generation, folderName);

    std::vector<Node*> interiorNodes = extractInteriorNodes(tree);
    for (auto& node : interiorNodes) {
        stream << getParentNodeString(node) << '\n';
    }
}

std::vector<Node*> IOHandler::extractInteriorNodes(Tree& tree) {
    std::vector<Node*> interiors;
    std::stack<Node*> nodes;
    nodes.push(&tree.root);
    while (!nodes.empty()) {
        Node* tmp = nodes.top();
        nodes.pop();
        for (auto& n : (*tmp).children)
            if (n.isParent())
                nodes.push(&n);
        interiors.push_back(tmp);
    }
    return interiors;
}