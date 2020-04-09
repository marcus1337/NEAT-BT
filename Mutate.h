
#include "Utils.h"
#include "Tree.h"

class Mutate {
    bool shouldMutate(float chance);

public:

    void mutateTree(Tree& tree);
};