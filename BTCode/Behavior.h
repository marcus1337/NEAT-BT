#include <vector>

#ifndef BEHAVIOR_H
#define BEHAVIOR_H

template <class T>
class Behavior {
private:

    std::vector<T> subVectors(std::vector<T> a, std::vector<T> b) {
        for (int i = 0; i < a.size(); i++)
            a[i] -= b[i];
        return a;
    }

    std::vector<T> addVectors(std::vector<T> a, std::vector<T> b) {
        for (int i = 0; i < a.size(); i++)
            a[i] += b[i];
        return a;
    }

    std::vector<T> divVectors(std::vector<T> a, const int divisor) {
        for (int i = 0; i < a.size(); i++)
            a[i] /= divisor;
        return a;
    }

public:

    std::vector<T> behaviors;

    Behavior<T> &operator+=(const Behavior<T> &rhs) {
        behaviors = addVectors(behaviors, rhs.behaviors);
        return *this;
    }

    Behavior<T> operator+(const Behavior<T> &rhs) {
        auto tmp = rhs;
        tmp += *this;
        return tmp;
    }

    Behavior<T> &operator-=(const Behavior<T> &rhs) {
        behaviors = subVectors(behaviors, rhs.behaviors);
        return *this;
    }

    const Behavior<T> operator-(const Behavior<T> &rhs) {
        Behavior<T> tmp = *this;
        tmp -= rhs;
        return tmp;
    }

    Behavior<T> operator/(const int &rhs) {
        Behavior<T> tmp = *this;
        tmp.behaviors = divVectors(tmp.behaviors, rhs);
        return tmp;
    }
};

#endif