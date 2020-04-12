#include "Tree.h"
#include <vector>
#include <string>

class IOHandler {
public:
    void makeFolder(std::string folderName);

public:
    std::vector<Tree> loadGeneration();
    Tree loadTree();
    void saveTree(Tree& tree, int generation, std::string folderName = "TREES");
    void saveGeneration(std::vector<Tree>& trees, int generation, std::string folderName = "TREES");

};