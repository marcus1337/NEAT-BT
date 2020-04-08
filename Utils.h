
#include <random>

#ifndef UTILS_H
#define UTILS_H


class Utils {
public:

    static std::random_device   mRd;
    static std::mt19937         mRng;
    static int randi(int LO, int HI);

};

#endif