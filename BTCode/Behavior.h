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
    std::vector<T> behaviors;

public:

    std::vector<T> get();
    void set(std::vector<T> vec);
    bool empty();

    Behavior<T> &operator+=(const std::vector<T> &rhs) {
        behaviors = addVectors(behaviors, rhs);
        return *this;
    }

    Behavior<T> &operator+=(const std::vector<int> &rhs) {
        *this += std::vector<T>(rhs.begin(), rhs.end());
        return *this;
    }

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

template <class T>
std::vector<T> Behavior<T>::get() {
    return behaviors;
}

template <class T>
void Behavior<T>::set(std::vector<T> vec) {
    behaviors = vec;
}

template <class T>
bool Behavior<T>::empty() {
    return behaviors.empty();
}

#endif