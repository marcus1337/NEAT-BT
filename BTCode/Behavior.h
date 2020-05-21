#include <vector>

template <class T>
class Behavior {
    std::vector<T> subVectors(std::vector<T> a, std::vector<T> b) const;
    std::vector<T> addVectors(std::vector<T> a, std::vector<T> b) const;
    std::vector<T> divVectors(std::vector<T> a, int divisor) const;

    Behavior<T> &operator+=(const Behavior<T> &rhs) {
        behaviors = addVectors(behaviors, rhs.behaviors);
        return *this;
    }
    const Behavior<T> operator+(const Behavior<T> &rhs) const {
        Behavior<T> tmp = *this;
        tmp += rhs;
        return tmp;
    }

    Behavior<T> &operator-=(const Behavior<T> &rhs) {
        behaviors = subVectors(behaviors, rhs.behaviors);
        return *this;
    }

    const Behavior<T> operator-(const Behavior<T> &rhs) const {
        Behavior<T> tmp = *this;
        tmp -= rhs;
        return tmp;
    }

    
    Behavior<T> &operator/=(const int &rhs) {
        behaviors = divVectors(behaviors, rhs);
        return *this;
    }

    const Behavior<T> operator/(const int &rhs) const {
        Behavior<T> tmp = *this;
        tmp /= rhs;
        return tmp;
    }

public:

    std::vector<T> behaviors;

};