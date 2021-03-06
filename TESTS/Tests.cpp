#define BOOST_TEST_MODULE TestBugs

#include "boost/test/unit_test.hpp"

#include "Tests.h"

#include "../BTCode/Node.h"
#include "../BTCode/IOHandler.h"
#include "../BTCode/Tree.h"

#include "../BTCode/Coordinator.h"
#include "../BTCode/Mutate.h"

#include "../BTCode/Selector.h"
#include "../BTCode/Breeder.h"
#include "../BTCode/Evolver.h"

#include "../BTCode/Behavior.h"

#include "../BTCode/TreeStringMapper.h"

using namespace std;
using namespace BTE;
namespace utf = boost::unit_test;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()


BOOST_AUTO_TEST_CASE(saveLoadSingle_test)
{
    TestUtils::setMaxNodeIDs(5000);
    IOHandler iohandler;
    std::string folderName = "TESTIO1";
    Tree tree = TestUtils::getRandomizedTree(50);
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
        trees.push_back(TestUtils::getRandomizedTree(50));

    iohandler.saveGeneration(trees,0, folderName);
    std::vector<Tree> loadedTrees = iohandler.loadGeneration(0, folderName);

    BOOST_REQUIRE(trees.size() == loadedTrees.size());
    rep(i, 0, sz(trees))
        BOOST_REQUIRE(trees[i].equals(loadedTrees[i]));
}

BOOST_AUTO_TEST_CASE(init_test)
{
    Coordinator coordinator;
    int n = 50;
    coordinator.init(n, 10, 10, 10, 10, 10);
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
    Tree tree = Tree::makeRandomTree(50);

    rep(i, 0, 50) {
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
    rep(i, 0, 50) {
        mutater.addNodeMutate(tree);
        Tree tmpCopy = tree.getValidTree();
        BOOST_REQUIRE(tree.equals(tmpCopy));
    }

    int numLeaves = tree.getNumberOfNodesOfType(ACTION) + tree.getNumberOfNodesOfType(CONDITION);
    BOOST_REQUIRE(numLeaves == 51);
}

BOOST_AUTO_TEST_CASE(mutateReplace_test)
{
    TestUtils::setMaxNodeIDs(50);
    Mutate mutater;
    mutater.mutateChance = 1.0f;
    Tree tree = TestUtils::getRandomizedTree(50);
    rep(i, 0, 3) {
        Tree tmpCopy = tree;
        mutater.replaceMutate(tree);
        auto nodes1 = tree.getNodesCopy();
        auto nodes2 = tmpCopy.getNodesCopy();
        BOOST_REQUIRE(nodes1.size() == nodes2.size());
        rep(j, 0, (int) nodes1.size()) {
            BOOST_REQUIRE(nodes1[j].isParent() == nodes2[j].isParent());
        }
    }
}

BOOST_AUTO_TEST_CASE(newGeneration_test)
{
    Coordinator coordinator;
    size_t n = 10;
    coordinator.init((int)n, 10, 10, 10, 10, 10);

    for (size_t i = 0; i < n; i++)
        coordinator.trees[i] = TestUtils::getRandomizedTree(50);

    Evolver evolver;
    auto newStuff = evolver.makeNewGeneration(coordinator.trees);
    
    BOOST_REQUIRE(newStuff.size() == coordinator.trees.size());
}

BOOST_AUTO_TEST_CASE(rootAlwaysParent_test)
{
    Coordinator coordinator;
    size_t n = 50;
    coordinator.init((int) n, 0, 0, 0, 0, 0);
    Evolver evolver;
    auto newStuff = evolver.makeNewGeneration(coordinator.trees);
    for(size_t i = 0 ; i < n ; i++)
        BOOST_REQUIRE(newStuff[i].root.isParent());
}

BOOST_AUTO_TEST_CASE(behaviorData_test)
{
    Behavior<float> behavior;

    behavior.set({ 0.f,1.f,50.f,1.5f });
    std::vector<float> correct = behavior.get();
    for (size_t i = 0; i < correct.size(); i++) {
        correct[i] = correct[i] / 2;
    }
    behavior -= (behavior/2);

    for (size_t i = 0; i < correct.size(); i++) {
        BOOST_REQUIRE(correct[i] == behavior.get()[i]);
    }

    behavior.set({ 0.f,1.f,50.f,1.5f });
    correct = behavior.get();
    for (size_t i = 0; i < correct.size(); i++) {
        correct[i] = correct[i] * 2;
    }
    behavior += behavior;

    for (size_t i = 0; i < correct.size(); i++) {
        BOOST_REQUIRE(correct[i] == behavior.get()[i]);
    }
}

BOOST_AUTO_TEST_CASE(surprise_test)
{
    Coordinator coordinator;
    size_t n = 50;
    coordinator.init((int)n, 50, 50, 50, 50, 50);
    for (size_t i = 0; i < n; i++) {
        coordinator.trees[i].fitness = 100;
        coordinator.trees[i].observedBehaviors = { 0,0,0 };
    }
    coordinator.setSurpriseEffect(1.0f);
    coordinator.trees[0].observedBehaviors = { 100,100,100 };
    coordinator.evolver.surprise.addSurpriseFitness(coordinator.trees);
    
    BOOST_REQUIRE(coordinator.trees[0].fitness > coordinator.trees[1].fitness*2);
}

BOOST_AUTO_TEST_CASE(randomTree_test)
{
    for (int i = 2; i < 10; i++) {
        Tree tree = Tree::makeRandomTree(i);
        BOOST_REQUIRE(tree.getNumberOfNodes() == i && tree.getValidTree().getNumberOfNodes() == i);
    }
}


BOOST_AUTO_TEST_CASE(mapElites_test)
{
    Coordinator coordinator;
    size_t n = 10;
    coordinator.init((int)n, 10, 10, 10, 10, 10);

    for (int i = 2; i < 10; i++) {
        coordinator.randomizePopulation(i, i);
        coordinator.mapElites();
    }
}

BOOST_AUTO_TEST_CASE(elitism_test)
{
    Coordinator coordinator;
    size_t n = 10;
    coordinator.init((int)n, 10, 10, 10, 10, 10);

    for (int i = 2; i < 10; i++) {
        coordinator.randomizePopulation(i, 10);
        for (int i = 0; i < n; i++) {
            coordinator.trees[i].fitness = i;
            coordinator.trees[i].observedBehaviors = { i, i, 0 };
        }
        coordinator.mapElites();
    }

    for(size_t i = 0 ; i < 5; i++)
        coordinator.evolver.mapElites.randomElitism(coordinator.trees);
}

BOOST_AUTO_TEST_CASE(saveLoadElites_test)
{
    TestUtils::setMaxNodeIDs(5000);
    IOHandler iohandler;
    std::string folderName = "TEST_ELITES";
    std::vector<Tree> trees;
    rep(i, 0, 50)
        trees.push_back(TestUtils::getRandomizedTree(50));
    MapElites mapElites;

    for (auto& tree : trees) {
        int a = Utils::randi(0, 99);
        int b = Utils::randi(0, 99);
        int c = Utils::randi(0, 99);
        tree.observedBehaviors = { a,b,c };
    }
    mapElites.storeElites(trees);

    iohandler.saveElites(mapElites.eliteTrees);
    auto loadedElites = iohandler.loadElites();

    BOOST_REQUIRE(mapElites.eliteTrees.size() == loadedElites.size());
    for (auto& tree : loadedElites) {
        BOOST_REQUIRE(tree.second.equals(mapElites.eliteTrees[tree.first]));
    }

}


BOOST_AUTO_TEST_CASE(treeStringMapper_test)
{
    TreeStringMapper mapper;
    Tree tree;
    Node::maxOtherInteriorID = 2;
    Node::maxDecoratorID = 2;
    Node::maxActionID = 2;
    Node::maxConditionID = 2;
    Node::maxUnorderedInteriorID = 2;
    
    tree = tree.makeRandomTree(10);
    string str = mapper.getMappedTreeString(tree);

    cout << "STR " << str << endl;
    BOOST_REQUIRE(mapper.getMappedTreeString(tree) == mapper.getMappedTreeString(tree));
    tree = tree.makeRandomTree(5);
    BOOST_REQUIRE(mapper.getMappedTreeString(tree) == mapper.getMappedTreeString(tree));

}


BOOST_AUTO_TEST_CASE(evolveWithBTDistance_test)
{
    Coordinator coordinator;
    coordinator.init(100, 4, 0, 0, 10, 10);

    /*for (size_t tests = 0; tests < 100; tests++) {
        coordinator.evolve();
        cout << "evo done: " << tests << "\n";
    }*/

}

BOOST_AUTO_TEST_CASE(sameSpecie_test)
{
    Coordinator coordinator;
    coordinator.init(2, 4, 0, 0, 5, 170);

    for (size_t tests = 0; tests < 100; tests++) {
        coordinator.randomizePopulation(55, 55);
        coordinator.evolver.speciator.setTreeStrings(coordinator.trees);
        bool tmp = coordinator.evolver.speciator.sameSpecie(coordinator.trees[0], coordinator.trees[1]);
        cout << "done: " << tmp << "\n";
    }

}