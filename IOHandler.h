#include "Tree.h"
#include <vector>
#include <string>
#include <fstream>
#include <stack>

#ifndef IOHANDLER_H
#define IOHANDLER_H


class IOHandler {
private:
    std::string generationInfoFileName = "Generation_Info";

    void makeFolder(std::string folderName);
    std::vector<Node*> extractInteriorNodes(Tree& tree);
    std::string getPath(std::string folderName);
    std::string getFolderName(int generation, std::string folderName);
    std::string getFilenameWithPath(std::string folderNameAndGeneration, int treeIndex);
    std::ofstream getFileOutStream(int treeIndex, int generation, std::string folderName);
    std::ifstream getFileInStream(int treeIndex, int generation, std::string folderName);
    std::string getParentNodeString(Node* node);

    std::ofstream getGenerationInfoOutStream(std::string folderName, int generation);
    std::ifstream getGenerationInfoInStream(std::string folderName, int generation);

    void saveTree(Tree& tree, std::ofstream& stream);
    std::vector<Node> loadTreeNodes(std::ifstream& stream);
    Node loadInteriorNode(std::ifstream& stream);
    Node loadNode(std::ifstream& stream);
    Tree loadTree(std::ifstream& stream);
    void addNodesToTree(std::vector<Node>& interiors, Tree& tree);
    void addNodeToTree(int interiorIndex, std::vector<Node>& interiors, std::stack<Node*>& nodeStack);
    void addParentsToStack(Node* node, std::stack<Node*>& nodeStack);

public:
    std::vector<Tree> loadGeneration(int generation, std::string folderName = "TREES");
    Tree loadTree(int treeIndex, int generation, std::string folderName = "TREES");
    void saveTree(Tree& tree, int treeIndex, int generation, std::string folderName = "TREES");
    void saveGeneration(std::vector<Tree>& trees, int generation, std::string folderName = "TREES");

};

#endif