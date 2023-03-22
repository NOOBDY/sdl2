#ifndef APP_H
#define APP_H

#include "triangle.h"

class App {
public:
    enum State {
        START,
        UPDATE,
        EXIT,
    };

    App();

    void OnStart();
    void OnUpdate();
    void OnExit();

    State GetCurrentState() { return m_CurrentState; }
    bool GetExit() { return m_Exit; }

private:
    State m_CurrentState;
    bool m_Exit;

    Triangle m_Triangle;
};

#endif
