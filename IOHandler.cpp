#include "IOHandler.h"
#include <filesystem>
#include <iostream>

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
    return getPath(std::string(folderNameAndGeneration + "//TREE_" + std::to_string(treeIndex) + ".txt"));
}

std::ofstream IOHandler::getFileOutStream(int treeIndex, int generation, std::string folderName) {
    std::string folderNameAndGeneration = getFolderName(generation, folderName);
    makeFolder(folderNameAndGeneration);
    return std::ofstream(getFilenameWithPath(folderNameAndGeneration, treeIndex));
}

std::ifstream IOHandler::getFileInStream(int treeIndex, int generation, std::string folderName) {
    std::string folderNameAndGeneration = getFolderName(generation, folderName);
    makeFolder(folderNameAndGeneration);
    return std::ifstream(getFilenameWithPath(folderNameAndGeneration, treeIndex));
}

std::string IOHandler::getParentNodeString(Node* node) {
    std::string res;
    res += std::string(std::to_string(node->children.size()) + " " + std::to_string(node->type) + " " + std::to_string(node->ID) + '\n');
    for (auto& n : node->children)
        res += std::string(std::to_string(n.type) + " " + std::to_string(n.ID)) + '\n';
    return res;
}

void IOHandler::saveTree(Tree& tree, std::ofstream& stream) {
    std::vector<Node*> interiorNodes = extractInteriorNodes(tree);
    stream << tree.fitness << '\n';
    stream << interiorNodes.size() << '\n';
    for (auto& node : interiorNodes)
        stream << getParentNodeString(node) << '\n';
}

void IOHandler::saveTree(Tree& tree, int treeIndex, int generation, std::string folderName) {
    std::ofstream stream = getFileOutStream(treeIndex, generation, folderName);
    saveTree(tree, stream);
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

Node IOHandler::loadNode(std::ifstream& stream) {
    Node res;
    int type;
    stream >> type >> res.ID;
    res.type = static_cast<NodeType>(type);
    return res;
}

Node IOHandler::loadInteriorNode(std::ifstream& stream) {
    int numChildren;
    stream >> numChildren;
    Node parent = loadNode(stream);
    for (int j = 0; j < numChildren; j++)
        parent.children.push_back(loadNode(stream));
    return parent;
}

std::vector<Node> IOHandler::loadTreeNodes(std::ifstream& stream) {
    std::vector<Node> res;
    int numParents;
    stream >> numParents;
    for (int i = 0; i < numParents; i++) {
        Node node = loadInteriorNode(stream);
        res.push_back(node);
    }
    return res;
}

void IOHandler::addParentsToStack(Node* node, std::stack<Node*>& nodeStack) {
    for (auto& n : node->children) {
        if (n.isParent())
            nodeStack.push(&n);
    }
}

void IOHandler::addNodeToTree(int interiorIndex, std::vector<Node>& interiors, std::stack<Node*>& nodeStack) {
    Node* node = nodeStack.top();
    nodeStack.pop();
    addParentsToStack(node, nodeStack);
    if (interiorIndex > 0)
        *node = interiors[interiorIndex];
}

void IOHandler::addNodesToTree(std::vector<Node>& interiors, Tree& tree) {
    std::stack<Node*> nodeStack;
    nodeStack.push(&tree.root);
    int interiorIndex = 0;

    while (!nodeStack.empty()) {
        addNodeToTree(interiorIndex, interiors, nodeStack);
        interiorIndex++;
    }
}

Tree IOHandler::loadTree(std::ifstream& stream) {
    Tree tree;
    stream >> tree.fitness;
    std::vector<Node> interiors = loadTreeNodes(stream);
    tree.root = interiors[0];
    addNodesToTree(interiors, tree);
    return tree;
}

Tree IOHandler::loadTree(int treeIndex, int generation, std::string folderName) {
    std::ifstream stream = getFileInStream(treeIndex, generation, folderName);
    return loadTree(stream);
}