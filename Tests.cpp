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


BOOST_AUTO_TEST_CASE(saveLoad_test)
{
    TestUtils::setMaxNodeIDs(5000);
    IOHandler iohandler;
    std::string folderName = "TESTIO";
    Tree tree = TestUtils::getRandomizedTree(100);
    iohandler.saveTree(tree, 0, 0, folderName);
    Tree otherTree = iohandler.loadTree(0, 0, folderName);
    BOOST_REQUIRE(tree.equals(otherTree));
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

BOOST_AUTO_TEST_CASE(mutateNode_test)
{
    Mutate mutater;
    mutater.mutateChance = 1;
    Tree tree;
    rep(i, 0, 300) {
        mutater.addNodeMutate(tree);
        Tree tmpCopy = tree.getValidTree();
        BOOST_REQUIRE(tree.equals(tmpCopy));
    }
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
        auto nodes1 = tree.getNodes();
        auto nodes2 = tmpCopy.getNodes();
        BOOST_REQUIRE(nodes1.size() == nodes2.size());
        rep(j, 0, nodes1.size()) {
            BOOST_REQUIRE(nodes1[j].type == nodes2[j].type);
        }
    }
}

BOOST_AUTO_TEST_CASE(tree_test)
{

}