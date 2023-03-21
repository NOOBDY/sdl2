#include <iostream>

#include "core/context.h"

#include "App.h"

int main(int argc, char **argv) {
    Core::CreateContext();

    App app;

    while (!app.GetExit()) {
        switch (app.GetCurrentState()) {
        case App::START:
            app.OnStart();
            break;

        case App::UPDATE:
            app.OnUpdate();
            break;

        case App::EXIT:
            app.OnExit();
            break;
        }
    }

    Core::DestroyContext();
}
