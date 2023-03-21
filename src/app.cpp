#include "app.h"

#include <iostream>

#include <glad/gl.h>

#include <SDL.h>

App::App() : m_CurrentState(App::START), m_Exit(false) {}

void App::OnStart() {
    std::cout << "Start\n";

    m_CurrentState = App::UPDATE;
}

void App::OnUpdate() {
    SDL_Event event;

    glClearColor(0.1f, 0.1f, 1.0f, 1.0f);

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
            m_CurrentState = App::EXIT;
        }
    }
}

void App::OnExit() {
    std::cout << "Exit\n";

    m_Exit = true;
}
