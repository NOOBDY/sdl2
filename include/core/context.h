#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <string>

#include <SDL.h>

namespace Core {
class Context {
public:
    Context(std::string title, int posX, int posY, int width, int height);
    ~Context();

    SDL_Window *GetWindow() const { return m_Window; }

private:
    SDL_Window *m_Window;
    SDL_GLContext m_Context;
};
} // namespace Core
#endif
