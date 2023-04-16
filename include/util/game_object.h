#ifndef UTIL_GAME_OBJECT_H
#define UTIL_GAME_OBJECT_H

namespace Util {
class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void Update() = 0;

private:
};
} // namespace Util
#endif
