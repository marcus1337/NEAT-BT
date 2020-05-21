#include "Behavior.h"

template <typename T>
std::vector<T> Behavior<T>::subVectors(std::vector<T> a, std::vector<T> b) const {
    for (int i = 0; i < behaviors.size(); i++)
        a[i] -= b[i];
    return a;
}
template <typename T>
std::vector<T> Behavior<T>::addVectors(std::vector<T> a, std::vector<T> b) const {
    for (int i = 0; i < behaviors.size(); i++)
        a[i] += b[i];
    return a;
}

template <typename T>
std::vector<T> Behavior<T>::divVectors(std::vector<T> a, int divisor) const {
    for (int i = 0; i < behaviors.size(); i++)
        a[i] /= divisor;
    return a;
}

//const Behavior Behavior::operator+(const Behavior &i) const;
