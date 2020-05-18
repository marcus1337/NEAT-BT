#include "Tree.h"
#include "TreeIterator.h"
#include "Utils.h"

Tree::Tree() {
    root = Node::makeRandomOtherInterior();
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

std::vector<Node> Tree::getNodesCopy() {
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

int Tree::getNumBranches() {
    int counter = 0;
    auto it = TreeIterator(root);
    while (it.hasNext()) {
        Node* tmp = it.next();
        counter += std::max(tmp->getNumInteriorChildren()-1,0);
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

Node* Tree::getRandomNonRootNode() {
    int numNodes = getNumberOfNodes();
    int randIndex = Utils::randi(2, numNodes);
    return getNodeAtIndex(randIndex);
}

Node* Tree::getRandomNode() {
    int numNodes = getNumberOfNodes();
    int randIndex = Utils::randi(1, numNodes);
    return getNodeAtIndex(randIndex);
}

int Tree::getNumberOfNodesOfType(NodeType nodeType) {
    int counter = 0;
    auto it = TreeIterator(root);
    while (it.hasNext()) {
        Node* tmp = it.next();
        if (tmp->type == nodeType)
            counter++;
    }
    return counter;
}

bool Tree::equals(Tree& other) {
    std::vector<Node> nodes1 = getNodesCopy();
    std::vector<Node> nodes2 = other.getNodesCopy();

    if (nodes1.size() != nodes2.size())
        return false;

    for (int i = 0; i < nodes1.size(); i++) {
        if (nodes1[i] != nodes2[i])
            return false;
    }

    return true;
}

void Tree::deleteLeaf(int position) {
    auto it = TreeIterator(root);
    while (it.hasNext()) {
        Node* tmp = it.next();
        if (tmp->isParent()) {
            for (int i = 0; i < tmp->children.size(); i++) {
                if (!tmp->children[i].isParent())
                    position--;
                if (position < 0) {
                    tmp->children.erase(tmp->children.begin() + i);
                    return;
                }
            }
        }
    }
}
void Tree::deleteCondition(int position) {
    auto it = TreeIterator(root);
    while (it.hasNext()) {
        Node* tmp = it.next();
        if (tmp->isParent()) {
            for (int i = 0; i < tmp->children.size(); i++) {
                if (tmp->children[i].type == CONDITION)
                    position--;
                if (position < 0) {
                    tmp->children.erase(tmp->children.begin() + i);
                    return;
                }
            }
        }
    }
}