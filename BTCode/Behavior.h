#include <vector>
#include <numeric>

#ifndef BEHAVIOR_H
#define BEHAVIOR_H

template <class T>
class Behavior {
private:

    std::vector<T> subVectors(std::vector<T> a, std::vector<T> b) const;
    std::vector<T> addVectors(std::vector<T> a, std::vector<T> b) const;
    std::vector<T> divVectors(std::vector<T> a, const int divisor) const;
    std::vector<T> multVectors(std::vector<T> a, std::vector<T> b) const;

    T sum();

    std::vector<T> behaviors;

public:

    T distance(std::vector<int> otherBehavior);

    std::vector<T> get();
    void set(std::vector<T> vec);
    bool empty();

    Behavior<T> &operator+=(const std::vector<T> &rhs) {
        behaviors = addVectors(behaviors, rhs);
        return *this;
    }

    Behavior<T> &operator*=(const std::vector<T> &rhs) {
        behaviors = multVectors(behaviors, rhs);
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

    Behavior<T> &operator*=(const Behavior<T> &rhs) {
        behaviors = multVectors(behaviors, rhs.behaviors);
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

    Behavior<T> &operator-=(const std::vector<T> &rhs) {
        behaviors = subVectors(behaviors, rhs);
        return *this;
    }

    Behavior<T> &operator-=(const std::vector<int> &rhs) {
        *this -= std::vector<T>(rhs.begin(), rhs.end());
        return *this;
    }

    const Behavior<T> operator-(const Behavior<T> &rhs) {
        Behavior<T> tmp = *this;
        tmp -= rhs;
        return tmp;
    }

    Behavior<T> &operator/=(const int &rhs) {
        behaviors = divVectors(behaviors, rhs);
        return *this;
    }

    Behavior<T> operator/(const int &rhs) const {
        Behavior<T> tmp = *this;
        tmp.behaviors = divVectors(tmp.behaviors, rhs);
        return tmp;
    }

};

template <class T>
std::vector<T> Behavior<T>::subVectors(std::vector<T> a, std::vector<T> b) const {
    for (size_t i = 0; i < a.size(); i++)
        a[i] -= b[i];
    return a;
}

template <class T>
std::vector<T> Behavior<T>::addVectors(std::vector<T> a, std::vector<T> b) const {
    for (size_t i = 0; i < a.size(); i++)
        a[i] += b[i];
    return a;
}

template <class T>
std::vector<T> Behavior<T>::divVectors(std::vector<T> a, const int divisor) const {
    for (size_t i = 0; i < a.size(); i++)
        a[i] /= divisor;
    return a;
}

template <class T>
std::vector<T> Behavior<T>::multVectors(std::vector<T> a, std::vector<T> b) const {
    for (size_t i = 0; i < a.size(); i++)
        a[i] *= b[i];
    return a;
}

template <class T>
T Behavior<T>::sum() {
    return std::accumulate(behaviors.begin(), behaviors.end(), T(0));
}

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

template <class T>
T Behavior<T>::distance(std::vector<int> otherBehavior) {
    Behavior<T> tmp = *this;
    tmp -= otherBehavior;
    tmp *= tmp;
    T dist = sqrt(tmp.sum());
    if (dist < T(1))
        return 0;
    return dist;
}

#endif