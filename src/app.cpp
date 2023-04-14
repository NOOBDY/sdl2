#include "app.h"

#include <iostream>

#include <GL/glew.h>

#include <SDL.h>

App::App() : m_CurrentState(App::START), m_Exit(false) {}

void App::OnStart() {
    std::cout << "Start\n";

    m_CurrentState = App::UPDATE;
}

void App::OnUpdate() {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
            m_CurrentState = App::EXIT;
        }
    }

    m_Triangle.OnUpdate();
}

void App::OnExit() {
    std::cout << "Exit\n";

    m_Exit = true;
}
