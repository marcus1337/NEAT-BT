#include "Tree.h"
#include <vector>
#include <string>
#include <fstream>

#ifndef IOHANDLER_H
#define IOHANDLER_H


class IOHandler {
private:
    void makeFolder(std::string folderName);
    std::vector<Node*> extractInteriorNodes(Tree& tree);
    std::string getPath(std::string folderName);
    std::string getFolderName(int generation, std::string folderName);
    std::string getFilenameWithPath(std::string folderNameAndGeneration, int treeIndex);
    std::ofstream getFileStream(int treeIndex, int generation, std::string folderName);
    std::string getParentNodeString(Node* node);

    std::string parentStartTag = "<P>";
    std::string parentEndTag = "</P>";

public:
    std::vector<Tree> loadGeneration();
    //Tree loadTree();
    void saveTree(Tree& tree, int treeIndex, int generation, std::string folderName = "TREES");
    //void saveGeneration(std::vector<Tree>& trees, int generation, std::string folderName = "TREES");

};

#endif