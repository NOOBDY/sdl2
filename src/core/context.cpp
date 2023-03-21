#include "core/context.h"

#include <iostream>

namespace Core {
void CreateContext() {
    std::cout << "Create Context\n";
}

void DestroyContext() {
    std::cout << "Destroy Context\n";
}
} // namespace Core
