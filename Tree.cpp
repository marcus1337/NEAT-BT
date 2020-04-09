#include "Tree.h"

void Tree::addParentsToQueue(std::queue<Node*>& nodes, Node* node) {
    for (auto& n : node->children) {
        if (n.isParent())
            nodes.push(&n);
    }
}

Node* Tree::popNodeQueue(std::queue<Node*>& nodes) {
    Node* node = nodes.front();
    nodes.pop();
    return node;
}

std::queue<Node*> Tree::makeNodeQueue() {
    std::queue<Node*> nodes;
    nodes.push(&root);
    return nodes;
}

int Tree::getNumberParentNodes() {
    int result = 0;
    std::queue<Node*> nodes = makeNodeQueue();
    while (!nodes.empty()) {
        Node* node = popNodeQueue(nodes);
        result++;
        addParentsToQueue(nodes, node);
    }

    return result;
}

Node* Tree::getNodeWithEmptyChild() {
    Node* result = nullptr;
    std::queue<Node*> nodes = makeNodeQueue();

    while (!nodes.empty()) {
        Node* node = popNodeQueue(nodes);
        for (auto& n : node->children) {
            if (n.isEmptyParent())
                return node;
        }
        addParentsToQueue(nodes, node);
    }

    return result;
}

bool Tree::removeEmptyChildrenFromNode(Node* node) {
    bool removedSomething = false;
    for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i].isEmptyParent()) {
            node->children.erase(node->children.begin() + i);
            i--;
            removedSomething = true;
        }
    }
    return removedSomething;
}

bool Tree::removeAllEmptyLeaves() {
    bool removedSomething = false;
    std::queue<Node*> nodes = makeNodeQueue();
    while (!nodes.empty()) {
        Node* node = popNodeQueue(nodes);
        if (removeEmptyChildrenFromNode(node))
            removedSomething = true;
        addParentsToQueue(nodes, node);
    }
    return removedSomething;
}

void Tree::removeAllEmptyChildren() {
    bool nodeRemoved = true;
    while (nodeRemoved)
        nodeRemoved = removeAllEmptyLeaves();
}

bool Tree::containsActionNode() {
    std::queue<Node*> nodes = makeNodeQueue();
    while (!nodes.empty()) {
        Node* node = popNodeQueue(nodes);
        if (node->type == ACTION)
            return true;
        addParentsToQueue(nodes, node);
    }
    return false;
}