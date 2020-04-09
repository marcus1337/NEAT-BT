#include "Mutate.h"
#include "Utils.h"

bool Mutate::shouldMutate(float chance) {
    return Utils::randf(0.f,1.f) < chance;
}

void Mutate::mutateTree(Tree& tree) {
    if (shouldMutate(0.01)) {

    }

}