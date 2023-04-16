#include "util/time.h"

#include <SDL.h>

Util::Time Time(); // static lifetime object

void Util::Time::Update() {
    s_Last = s_Now;
    s_Now = SDL_GetPerformanceCounter();

    s_DeltaTime =
        (s_Now - s_Last) / static_cast<double>(SDL_GetPerformanceFrequency());
}

double Util::Time::s_Now = SDL_GetPerformanceCounter();
double Util::Time::s_Last = 0;
double Util::Time::s_DeltaTime = 0;