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
        return Node::makeRandomInterior();
    if (randFloat > 0.85f)
        return Node::makeRandomCondition();
    if (randFloat > 0.6f)
        return Node::makeRandomInterior();
    return Node::makeRandomCondition();
}

void Mutate::addNodeMutate(Tree& tree) {
    if (shouldMutate(mutateChance)) {
        Node* node = tree.getEmptyParent();
        if (node != nullptr)
            node->addChild(makeRandomNode());
        else
            getRandomParent(tree)->addChild(makeRandomNode());
    }
}

Node* Mutate::getRandomParent(Tree& tree) {
    std::vector<Node*> parents = getParents(tree);
    int randomIndex = Utils::randi(0, parents.size());
    return parents[randomIndex];
}
std::vector<Node*> Mutate::getParents(Tree& tree) {
    std::vector<Node*> res;
    auto it = TreeIterator(tree.root);
    while (it.hasNext()) {
        Node* node = it.next();
        if (node->isParent())
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