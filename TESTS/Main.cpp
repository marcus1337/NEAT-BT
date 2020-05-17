/*#include <iostream>

#include "Node.h"
#include "Coordinator.h"
#include "IOHandler.h"

using namespace std;

int main() {

    Coordinator coordinator;
    coordinator.init(10, 10, 10, 10, 10);
    IOHandler iohandler;

    iohandler.saveTree(coordinator.trees[0],1,4);
    Tree tree = iohandler.loadTree(1, 4);
    iohandler.saveGeneration(coordinator.trees, 5);

    return 0;
}*/