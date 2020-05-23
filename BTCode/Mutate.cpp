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
    int numNodes = tree.getNumberOfNodes() - 1;
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
    Node newNode = makeRandomNode();
    Node* interior = getRandomInterior(tree);
    interior->addChild(newNode);
    while (newNode.isParent()) {
        interior = getEmptyParentChild(interior);
        newNode = makeRandomNode();
        interior->addChild(newNode);
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
    int randomIndex = Utils::randi(0, (int)(parents.size() - 1));
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

bool Mutate::hasMultipleActions(Tree& tree) {
    return tree.getNumberOfNodesOfType(ACTION) > 1;
}

void Mutate::deleteNodeMutate(Tree& tree) {

    std::vector<std::tuple<Node*, int>> deletables = getDeletableNodes(tree);
    if (deletables.empty())
        return;

    int randomIndex = Utils::randi(0, deletables.size() - 1);
    Node* parentNode = std::get<0>(deletables[randomIndex]);
    int childIndex = std::get<1>(deletables[randomIndex]);


    if (!parentNode->children[childIndex].isParent()) {
        parentNode->children.erase(parentNode->children.begin() + childIndex);
    }
    else {
        auto movedChildren = parentNode->children[childIndex].children;
        parentNode->children.erase(parentNode->children.begin() + childIndex);
        auto it = parentNode->children.begin();
        parentNode->children.insert(it + childIndex, movedChildren.begin(), movedChildren.end());
    }

    tree = tree.getValidTree();
}

std::vector<std::tuple<Node*, int>> Mutate::getDeletableNodes(Tree& tree) {
    std::vector<std::tuple<Node*, int>> deletables;
    bool canDeleteAction = hasMultipleActions(tree);
    auto it = TreeIterator(tree.root);
    while (it.hasNext()) {
        InfoNode infoNode = it.nextInfo();
        if (infoNode.parentNode == nullptr)
            continue;
        Node* node = infoNode.node;
        if (node->isParent()) {
            for (size_t i = 0; i < node->children.size(); i++) {
                if (canDeleteAction && node->children[i].type == ACTION)
                    deletables.push_back(std::make_tuple(node, i));
                else if (node->children[i].type == CONDITION)
                    deletables.push_back(std::make_tuple(node, i));
            }
        }
        if (node->isParent() && node->children.size() == 1 && node->children[0].isParent())
            deletables.push_back(std::make_tuple(infoNode.parentNode, 0));
    }
    return deletables;
}

void Mutate::mutateTree(Tree& tree) {
    if (shouldMutate(mutateChance / 2.f))
        deleteNodeMutate(tree);

    if (shouldMutate(mutateChance))
        replaceMutate(tree);

    if (shouldMutate(mutateChance))
        addNodeMutate(tree);
}