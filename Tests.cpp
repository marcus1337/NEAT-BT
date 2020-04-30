#define BOOST_TEST_MODULE TestBugs
#include "boost/test/unit_test.hpp"

#include "Tests.h"

#include "Node.h"
#include "IOHandler.h"
#include "Tree.h"
#include "Coordinator.h"
#include "Mutate.h"

using namespace std;
namespace utf = boost::unit_test;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()


BOOST_AUTO_TEST_CASE(saveLoadSingle_test)
{
    TestUtils::setMaxNodeIDs(5000);
    IOHandler iohandler;
    std::string folderName = "TESTIO1";
    Tree tree = TestUtils::getRandomizedTree(100);
    iohandler.saveTree(tree, 0, 0, folderName);
    Tree otherTree = iohandler.loadTree(0, 0, folderName);
    BOOST_REQUIRE(tree.equals(otherTree));
}

BOOST_AUTO_TEST_CASE(saveLoadGeneration_test)
{
    TestUtils::setMaxNodeIDs(5000);
    IOHandler iohandler;
    std::string folderName = "TESTIO2";
    std::vector<Tree> trees;
    rep(i, 0, 50)
        trees.push_back(TestUtils::getRandomizedTree(100));

    iohandler.saveGeneration(trees,0, folderName);
    std::vector<Tree> loadedTrees = iohandler.loadGeneration(0, folderName);

    BOOST_REQUIRE(trees.size() == loadedTrees.size());
    rep(i, 0, sz(trees))
        BOOST_REQUIRE(trees[i].equals(loadedTrees[i]));
}

BOOST_AUTO_TEST_CASE(init_test)
{
    Coordinator coordinator;
    int n = 100;
    coordinator.init(n, 10, 10, 10, 10);
    BOOST_REQUIRE(sz(coordinator.trees) == n);
    rep(i, 0, n) {
        BOOST_REQUIRE(coordinator.trees[i].getNumberOfNodes() == 2);
        BOOST_REQUIRE(coordinator.trees[i].getValidTree().equals(coordinator.trees[i]));
    }
}

BOOST_AUTO_TEST_CASE(mutateDeleteNode_test)
{
    Mutate mutater;
    mutater.mutateChance = 9999;
    Tree tree = TestUtils::getRandomizedTree(300);

    rep(i, 0, 300) {
        mutater.deleteNodeMutate(tree);
        Tree tmpCopy = tree.getValidTree();
        BOOST_REQUIRE(tree.equals(tmpCopy));
    }

    int numLeaves = tree.getNumberOfNodesOfType(ACTION) + tree.getNumberOfNodesOfType(CONDITION);
    BOOST_REQUIRE(numLeaves == 1);
}

BOOST_AUTO_TEST_CASE(mutateNode_test)
{
    Mutate mutater;
    mutater.mutateChance = 9999;
    Tree tree;
    rep(i, 0, 300) {
        mutater.addNodeMutate(tree);
        Tree tmpCopy = tree.getValidTree();
        BOOST_REQUIRE(tree.equals(tmpCopy));
    }

    int numLeaves = tree.getNumberOfNodesOfType(ACTION) + tree.getNumberOfNodesOfType(CONDITION);
    BOOST_REQUIRE(numLeaves == 301);
}

BOOST_AUTO_TEST_CASE(mutateReplace_test)
{
    TestUtils::setMaxNodeIDs(50);
    Mutate mutater;
    mutater.mutateChance = 1.0f;
    Tree tree = TestUtils::getRandomizedTree(300);
    rep(i, 0, 3) {
        Tree tmpCopy = tree;
        mutater.replaceMutate(tree);
        auto nodes1 = tree.getNodesCopy();
        auto nodes2 = tmpCopy.getNodesCopy();
        BOOST_REQUIRE(nodes1.size() == nodes2.size());
        rep(j, 0, nodes1.size()) {
            BOOST_REQUIRE(nodes1[j].type == nodes2[j].type);
        }
    }
}

BOOST_AUTO_TEST_CASE(tree_test)
{

}