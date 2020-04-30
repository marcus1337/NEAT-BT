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
    //BOOST_CHECK(add(2, 2) == 4);
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

BOOST_AUTO_TEST_CASE(mutateTree_test)
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

BOOST_AUTO_TEST_CASE(tree_test)
{

}