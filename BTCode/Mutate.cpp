#include "Mutate.h"
#include "Utils.h"
#include "TreeIterator.h"

bool Mutate::shouldMutate(float chance) {
    return Utils::randf(0.f, 1.f) < chance;
}

void Mutate::replaceRandomly(Node* node) {
    if (node->type == OTHER_INTERIOR)
        node->ID = Node::makeRandomOtherInterior().ID;
    if (node->type == UNORDERED_INTERIOR)
        node->ID = Node::makeRandomUnorderedInterior().ID;
    if (node->type == DECORATOR)
        node->ID = Node::makeRandomDecorator().ID;
    if (node->type == ACTION)
        node->ID = Node::makeRandomAction().ID;
    if (node->type == CONDITION)
        node->ID = Node::makeRandomCondition().ID;
}

void Mutate::replaceMutate(Tree& tree) {
    if (!shouldMutate(mutateChance))
        return;

    int numNodes = tree.getNumberOfNodes()-1;
    int randNodeIndex = Utils::randi(0, numNodes);

    auto it = TreeIterator(tree.root);
    while (it.hasNext()) {
        Node* node = it.next();
        if (randNodeIndex == 0) {
            replaceRandomly(node);
            break;
        }
        randNodeIndex--;
    }
}

Node Mutate::makeRandomNode() {
    float randFloat = Utils::randf(0.f, 1.f);
    if (randFloat > 0.98f)
        return Node::makeRandomDecorator();
    if (randFloat > 0.85f)
        return Node::makeRandomCondition();
    if (randFloat > 0.65f)
        return Node::makeRandomOtherInterior();
    if (randFloat > 0.60f)
        return Node::makeRandomUnorderedInterior();
    return Node::makeRandomAction();
}

void Mutate::addNodeMutate(Tree& tree) {
    if (shouldMutate(mutateChance)) {
        Node newNode = makeRandomNode();
        Node* interior = getRandomInterior(tree);
        interior->addChild(newNode);
        while (newNode.isParent()) {
            interior = getEmptyParentChild(interior);
            newNode = makeRandomNode();
            interior->addChild(newNode);
        }
    }
}

Node* Mutate::getEmptyParentChild(Node* node) {
    for (size_t i = 0; i < node->children.size(); i++)
        if (node->children[i].isEmptyParent())
            return &node->children[i];
    return nullptr;
}

Node* Mutate::getRandomInterior(Tree& tree) {
    std::vector<Node*> parents = getInteriors(tree);
    int randomIndex = Utils::randi(0, (int) (parents.size() - 1));
    return parents[randomIndex];
}

std::vector<Node*> Mutate::getInteriors(Tree& tree) {
    std::vector<Node*> res;
    auto it = TreeIterator(tree.root);
    while (it.hasNext()) {
        Node* node = it.next();
        if (node->isParent() && node->type != DECORATOR)
            res.push_back(node);
    }
    return res;
}

void Mutate::deleteNodeMutate(Tree& tree) {
    if (shouldMutate(mutateChance / 2.f)) {
        int numActions = tree.getNumberOfNodesOfType(ACTION);
        int numConditions = tree.getNumberOfNodesOfType(CONDITION);
        if (numActions == 1) {
            if (numConditions == 0)
                return;
            int pickedNumber = Utils::randi(0, numConditions - 1);
            tree.deleteCondition(pickedNumber);
        }
        else {
            int pickedNumber = Utils::randi(0, numConditions + numActions - 1);
            tree.deleteLeaf(pickedNumber);
        }
        tree = tree.getValidTree();
    }
}

void Mutate::mutateTree(Tree& tree) {
    deleteNodeMutate(tree);
    replaceMutate(tree);
    addNodeMutate(tree);
}