#include "Node.h"
#include "Utils.h"
#include <assert.h>

void Node::addChild(Node node) {
    assert(isParent());
    int randomPosition = Utils::randi(0, children.size());
    if (randomPosition == children.size())
        children.push_back(node);
    else
        children.insert(children.begin() + randomPosition, node);
}

bool Node::isParent() {
    return type == INTERIOR || type == DECORATOR;
}

int Node::maxActionID;
int Node::maxConditionID;
int Node::maxDecoratorID;
int Node::maxInteriorID;

Node Node::makeRandomInterior() {
    Node node;
    node.type = INTERIOR;
    node.ID = Utils::randi(0, Node::maxInteriorID);
    return node;
}

Node Node::makeRandomDecorator() {
    Node node;
    node.type = DECORATOR;
    node.ID = Utils::randi(0, Node::maxDecoratorID);
    return node;
}

Node Node::makeRandomAction() {
    Node node;
    node.type = ACTION;
    node.ID = Utils::randi(0, Node::maxActionID);
    return node;
}

Node Node::makeRandomCondition() {
    Node node;
    node.type = CONDITION;
    node.ID = Utils::randi(0, Node::maxConditionID);
    return node;
}