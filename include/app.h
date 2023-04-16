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

    void Start();
    void Update();
    void Exit();

    State GetCurrentState() { return m_CurrentState; }
    bool GetExit() { return m_Exit; }

private:
    State m_CurrentState;
    bool m_Exit;

    Triangle m_Triangle;
};

#endif
