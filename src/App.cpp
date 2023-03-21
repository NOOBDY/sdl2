#include "App.h"

#include <iostream>

App::App() : m_CurrentState(App::START), m_Exit(false) {}

void App::OnStart() {
    std::cout << "Start\n";

    m_CurrentState = App::UPDATE;
}

void App::OnUpdate() {
    for (int i = 0; i < 5; i++) {
        std::cout << "Update " << i << "\n";
    }

    m_CurrentState = App::EXIT;
}

void App::OnExit() {
    std::cout << "Exit\n";

    m_Exit = true;
}
