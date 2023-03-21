#include "core/context.h"

#include <iostream>

#include <glad/gl.h>

#include <SDL_opengl.h>

namespace Core {
Context::Context(std::string title, int posX, int posY, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL\n";
        std::cout << SDL_GetError() << "\n";
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

    m_Window = SDL_CreateWindow(             //
        title.c_str(),                       // Title name
        posX,                                // Position X
        posY,                                // Position Y
        width,                               // Width
        height,                              // Height
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN // Flags
    );

    m_Context = SDL_GL_CreateContext(m_Window); // Currently unused

    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress))) {
        GLuint err = glad_glGetError();
        std::cout << "Failed to initialize OpenGL\n";
        std::cout << glad_glGetString(err);
    }
}

Context::~Context() {
    SDL_DestroyWindow(m_Window);

    SDL_Quit();
}
} // namespace Core
