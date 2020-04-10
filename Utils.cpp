#include "Utils.h"

std::random_device   Utils::mRd;
std::mt19937         Utils::mRng(Utils::mRd());

int Utils::randi(int LO, int HI) {
    std::uniform_int_distribution<> distr(LO, HI);
    return distr(mRng);
}

float Utils::randf(float LO, float HI) {
    std::uniform_real_distribution<> distr(LO, HI);
    return distr(mRng);
}

bool Utils::randb() {
    std::uniform_int_distribution<> distr(0, 1);
    return distr(mRng);
}