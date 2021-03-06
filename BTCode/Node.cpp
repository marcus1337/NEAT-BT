#include "Node.h"
#include "Utils.h"
#include <assert.h>

void Node::addChild(Node node) {
    assert(isParent());
    int randomPosition = Utils::randi(0, (int) children.size());
    if (randomPosition == children.size())
        children.push_back(node);
    else
        children.insert(children.begin() + randomPosition, node);
}

int Node::getNumInteriorChildren() {
    if (!isParent())
        return 0;
    int counter = 0;
    for (size_t i = 0; i < children.size(); i++) {
        if (children[i].isParent())
            counter++;
    }
    return counter;
}

bool Node::isParent() {
    return type == OTHER_INTERIOR || type == UNORDERED_INTERIOR || type == DECORATOR;
}
bool Node::isEmptyParent() {
    return isParent() && children.empty();
}

int Node::maxActionID;
int Node::maxConditionID;
int Node::maxDecoratorID;
int Node::maxOtherInteriorID;
int Node::maxUnorderedInteriorID;

Node Node::makeRandomOtherInterior() {
    Node node;
    node.type = OTHER_INTERIOR;
    node.ID = Utils::randi(0, Node::maxOtherInteriorID);
    return node;
}

Node Node::makeRandomUnorderedInterior() {
    Node node;
    node.type = UNORDERED_INTERIOR;
    node.ID = Utils::randi(0, Node::maxUnorderedInteriorID);
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

bool Node::operator<(const Node &right) const {
    if (type == right.type)
        return ID < right.ID;
    return type < right.type;
}

bool Node::operator==(Node const& right) const {
    return type == right.type && ID == right.ID;
}

bool Node::operator!=(Node const& right) const {
    return !(*this == right);
}