#include "IOHandler.h"
#include <filesystem>
#include <iostream>
#include "GenerationInfo.h"

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

void IOHandler::addParentsToStack(Node* node, std::stack<Node*>& nodeStack) {
    for (auto& n : node->children) {
        if (n.isParent()) {
            nodeStack.push(&n);
        }
    }
}

void IOHandler::addNodeToTree(int interiorIndex, std::vector<Node>& interiors, std::stack<Node*>& nodeStack) {
    Node* node = nodeStack.top();
    nodeStack.pop();
    if (interiorIndex > 0)
        *node = interiors[interiorIndex];
    addParentsToStack(node, nodeStack);
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

Node IOHandler::loadInteriorNode(std::ifstream& stream) {
    int numChildren;
    stream >> numChildren;
    Node parent = loadNode(stream);
    for (int j = 0; j < numChildren; j++)
        parent.children.push_back(loadNode(stream));
    return parent;
}

Node IOHandler::loadNode(std::ifstream& stream) {
    Node res;
    int type;
    stream >> type >> res.ID;
    res.type = static_cast<NodeType>(type);
    return res;
}

Tree IOHandler::loadTree(int treeIndex, int generation, std::string folderName) {
    std::ifstream stream = getFileInStream(treeIndex, generation, folderName);
    return loadTree(stream);
}

std::ofstream IOHandler::getGenerationInfoOutStream(std::string folderName, int generation) {
    std::string folderNameAndGeneration = getFolderName(generation, folderName);
    makeFolder(folderNameAndGeneration);
    return std::ofstream(getPath(std::string(folderNameAndGeneration + "//" + generationInfoFileName + ".txt")));
}

void IOHandler::saveGeneration(std::vector<Tree>& trees, int generation, std::string folderName) {
    std::ofstream infoStream = getGenerationInfoOutStream(folderName, generation);
    GenerationInfo generationInfo;
    generationInfo.generation = generation;
    generationInfo.saveData(infoStream, trees);

    for (int i = 0; i < trees.size(); i++)
        saveTree(trees[i], i + 1, generation, folderName);
}

std::ifstream IOHandler::getGenerationInfoInStream(std::string folderName, int generation) {
    std::string folderNameAndGeneration = getFolderName(generation, folderName);
    makeFolder(folderNameAndGeneration);
    return std::ifstream(getPath(std::string(folderNameAndGeneration + "//" + generationInfoFileName + ".txt")));
}

std::vector<Tree> IOHandler::loadGeneration(int generation, std::string folderName) {
    std::vector<Tree> result;
    GenerationInfo generationInfo;
    generationInfo.generation = generation;
    std::ifstream infoStream = getGenerationInfoInStream(folderName, generation);
    generationInfo.loadData(infoStream);

    for (int i = 0; i < generationInfo.numTrees; i++) {
        Tree tree = loadTree(i + 1, generation, folderName);
        result.push_back(tree);
    }

    return result;
}