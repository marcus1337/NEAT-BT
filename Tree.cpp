#include "Tree.h"
#include "TreeIterator.h"
#include "Utils.h"

Tree::Tree() {
    root = Node::makeRandomInterior();
    root.addChild(Node::makeRandomAction());
}

Tree Tree::getValidTree() {
    Tree tree = *this;
    tree.removeAllEmptyChildren();
    return tree;
}

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

Node* Tree::getEmptyParent() {
    Node* node = getNodeWithEmptyChild();
    if (node != nullptr)
        for (auto& n : node->children)
            if (n.isEmptyParent())
                return node;
    return node;
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

std::vector<Node> Tree::getNodes() {
    std::vector<Node> result;
    auto it = TreeIterator(root);
    while (it.hasNext()) {
        Node* node = it.next();
        Node nodInfo;
        nodInfo.type = node->type;
        nodInfo.ID = node->ID;
        result.push_back(nodInfo);
    }
    return result;
}

int Tree::getNumberOfNodes() {
    int counter = 0;
    auto it = TreeIterator(root);
    while (it.hasNext()) {
        it.next();
        counter++;
    }
    return counter;
}

Node* Tree::getNodeAtIndex(int index) {
    int counter = 0;
    auto it = TreeIterator(root);
    while (it.hasNext()) {
        Node* tmp = it.next();
        counter++;
        if (counter == index)
            return tmp;
    }
    return nullptr;
}

Node* Tree::getRandomNode() {
    int numNodes = getNumberOfNodes();
    int randIndex = Utils::randi(0, numNodes);
    return getNodeAtIndex(randIndex);
}