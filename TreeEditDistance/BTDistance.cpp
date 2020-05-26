
#include "BTDistance.h"


#include "APTED/apted_tree_index.h"
#include "APTED/bracket_notation_parser.h"
#include "APTED/touzet_baseline_tree_index.h"
#include "APTED/unit_cost_model.h"
#include "APTED/node.h"
#include "APTED/tree_indexer.h"

#include <limits>

typedef label::StringLabel Label;
typedef cost_model::UnitCostModelLD<label::StringLabel> CostModel;
typedef label::LabelDictionary<label::StringLabel> LabelDictionary;

int BTDistance::calculateLimitedTreeEditDistance(std::string treeStr1, std::string treeStr2, int maxVal) {

    LabelDictionary ld;
    CostModel ucm(ld);
    ted::TouzetBaselineTreeIndex<CostModel, node::TreeIndexAll> touzet_baseline_algorithm(ucm);

    node::TreeIndexAll ti1;
    node::TreeIndexAll ti2;
    parser::BracketNotationParser bnp;
    
    node::Node<Label> t1 = bnp.parse_single(treeStr1);
    node::Node<Label> t2 = bnp.parse_single(treeStr2);
    node::index_tree(ti1, t1, ld, ucm);
    node::index_tree(ti2, t2, ld, ucm);

    double computed_results = touzet_baseline_algorithm.ted_k(ti1, ti2, maxVal);
    if (computed_results == std::numeric_limits<double>::infinity())
        return std::numeric_limits<int>::max();
    return (int)computed_results;
}

int BTDistance::calculateTreeEditDistance(std::string treeStr1, std::string treeStr2) {
    LabelDictionary ld;
    CostModel ucm(ld);
    ted::TEDAlgorithm<CostModel, node::TreeIndexAll>* ted_algorithm;
    ted::APTEDTreeIndex<CostModel, node::TreeIndexAll> apted_algorithm(ucm);
    ted_algorithm = &apted_algorithm;

    node::TreeIndexAll ti1;
    node::TreeIndexAll ti2;
    parser::BracketNotationParser bnp;

    node::Node<Label> t1 = bnp.parse_single(treeStr1);
    node::Node<Label> t2 = bnp.parse_single(treeStr2);
    node::index_tree(ti1, t1, ld, ucm);
    node::index_tree(ti2, t2, ld, ucm);
    double computed_results = ted_algorithm->ted(ti1, ti2);
    return (int)computed_results;
}