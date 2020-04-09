#include "Tree.h"
#include <queue>


int Tree::getNumberParentNodes() {
    int result = 0;
    std::queue<Node*> nodes;
    nodes.push(&root);

    while (!nodes.empty()) {
        Node* node = nodes.front();
        nodes.pop();
        result++;
        for (auto& n : node->children) {
            if (n.isParent())
                nodes.push(&n);
        }
    }

    return result;
}