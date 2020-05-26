#include <string>
#include <vector>

class BTDistance {
public:

    int calculateTreeEditDistance(std::string treeStr1, std::string treeStr2);
    int calculateLimitedTreeEditDistance(std::string treeStr1, std::string treeStr2, int maxVal);

};