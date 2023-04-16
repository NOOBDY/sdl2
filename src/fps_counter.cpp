#include "fps_counter.h"

#include <iostream>

#include <SDL_ttf.h>

#include <fmt/core.h>

#include "util/time.h"

FpsCounter::FpsCounter() {
    std::string filepath = "../assets/fonts/lazy.ttf";

    m_Font = TTF_OpenFont(filepath.c_str(), 12);

    if (!m_Font) {
        std::cout << fmt::format("Failed to load font: '{}'\n", filepath);
    }

    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

FpsCounter::~FpsCounter() {
    TTF_CloseFont(m_Font);
}

void FpsCounter::Update() {
    SDL_Surface *surface = TTF_RenderText_Solid(m_Font, "Test", {0, 0, 0});

    if (!surface) {
        std::cout << "Failed to render text surface\n";
        std::cout << TTF_GetError() << "\n";
        return;
    }

    unsigned int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    if (!surface) {
        std::cout << "Unable to render text surface\n";
        std::cout << TTF_GetError() << "\n";
    }

    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode,
                 GL_UNSIGNED_BYTE, surface->pixels);

    std::cout << fmt::format("{:.02f}\n", 1.0F / Util::Time::GetDeltaTime());

    SDL_FreeSurface(surface);
}