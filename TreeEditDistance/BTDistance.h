#include <string>
#include <vector>


#ifndef BTDISTANCE_H
#define BTDISTANCE_H


class BTDistance {
public:



    int calculateTreeEditDistance(std::string treeStr1, std::string treeStr2);
    int calculateLimitedTreeEditDistance(std::string treeStr1, std::string treeStr2, int maxVal);

};

#endif // !BTDISTANCE_H