#include "util/time.h"

#include <SDL.h>

Time Time(); // static lifetime object

void Time::Update() {
    s_Last = s_Now;
    s_Now = SDL_GetPerformanceCounter();

    s_DeltaTime =
        (s_Now - s_Last) / static_cast<double>(SDL_GetPerformanceFrequency());
}

double Time::s_Now = SDL_GetPerformanceCounter();
double Time::s_Last = 0;
double Time::s_DeltaTime = 0;