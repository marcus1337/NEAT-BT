
#include "Utils.h"
#include "Tree.h"

class Mutate {
    bool shouldMutate(float chance);
    void replaceRandomly(Node* node);
    Node makeRandomNode();

    Node* getRandomParent(Tree& tree);
    std::vector<Node*> getParents(Tree& tree);
public:

    float mutateChance = 0.01f;

    void addNodeMutate(Tree& tree);
    void replaceMutate(Tree& tree);
    void enableMutate(Tree& tree);

    void mutateTree(Tree& tree);
};