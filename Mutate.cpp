#include "Mutate.h"
#include "Utils.h"
#include "TreeIterator.h"

bool Mutate::shouldMutate(float chance) {
    return Utils::randf(0.f,1.f) < chance;
}

void Mutate::replaceRandomly(Node* node) {
    if (node->type == INTERIOR)
        node->ID = Node::makeRandomInterior().ID;
    if (node->type == DECORATOR)
        node->ID = Node::makeRandomInterior().ID;
    if (node->type == ACTION)
        node->ID = Node::makeRandomAction().ID;
    if (node->type == CONDITION)
        node->ID = Node::makeRandomCondition().ID;
}

void Mutate::replaceMutate(Tree& tree) {
    auto it = TreeIterator(tree.root);
    while (it.hasNext()) {
        Node* node = it.next();
        if (shouldMutate(mutateChance)) {
            replaceRandomly(node);
        }
    }
}

Node Mutate::makeRandomNode() {
    float randFloat = Utils::randf(0.f, 1.f);
    if (randFloat > 0.97f)
        return Node::makeRandomDecorator();
    if (randFloat > 0.85f)
        return Node::makeRandomCondition();
    if (randFloat > 0.65f)
        return Node::makeRandomInterior();
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
    for (int i = 0; i < node->children.size(); i++)
        if (node->children[i].isEmptyParent())
            return &node->children[i];
    return nullptr;
}

Node* Mutate::getRandomInterior(Tree& tree) {
    std::vector<Node*> parents = getInteriors(tree);
    int randomIndex = Utils::randi(0, parents.size()-1);
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

void Mutate::enableMutate(Tree& tree) {
    auto it = TreeIterator(tree.root);
    while (it.hasNext()) {
        Node* node = it.next();
        if (shouldMutate(mutateChance))
            node->enabled = !node->enabled;
    }
}

void Mutate::mutateTree(Tree& tree) {
    //enableMutate(tree);
    replaceMutate(tree);
    addNodeMutate(tree);
}