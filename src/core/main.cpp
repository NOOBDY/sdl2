#include <iostream>

#include <SDL.h>

#define GUARD
#include "core/context.h"

#include "util/time.h"

#include "config.h"
#include "app.h"

int main(int argc, char **argv) {
    Core::Context context(       //
        "Framework",             // Title name
        SDL_WINDOWPOS_UNDEFINED, // Position X
        SDL_WINDOWPOS_UNDEFINED, // Position Y
        SCREEN_WIDTH,            // Width
        SCREEN_HEIGHT            // Height
    );

    App app;

    while (!app.GetExit()) {
        glClear(GL_COLOR_BUFFER_BIT);

        switch (app.GetCurrentState()) {
        case App::START:
            app.Start();
            break;

        case App::UPDATE:
            app.Update();
            break;

        case App::EXIT:
            app.Exit();
            break;
        }

        Util::Time::Update();
        SDL_GL_SwapWindow(context.GetWindow());
    }
}
