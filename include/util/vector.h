#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

namespace Util {
template <typename T>
struct Vector2 {
    union {
        T x, r;
        T y, g;
    };
};

template <typename T>
struct Vector3 {
    union {
        T x, r;
        T y, g;
        T z, b;
    };
};
} // namespace Util

#endif
