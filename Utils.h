
#include <random>

#ifndef UTILS_H
#define UTILS_H


class Utils {
public:

    static std::random_device   mRd;
    static std::mt19937         mRng;
    static int randi(int LO, int HI);
    static float randf(float LO, float HI);
    static bool randb();

    static int randIndex(std::vector<int> probabilties);

    template<typename T>
    static void swapPointers(T** p1, T** p2)
    {
        T* tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
    }

};

#endif