#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <string>

#include <GL/glew.h>

#include <SDL_ttf.h>

#include <util/game_object.h>

class FpsCounter : public Util::GameObject {
public:
    FpsCounter();
    ~FpsCounter() override;

    void Update() override;

private:
    /**
     * Probably not the most performant way to do it
     * https://www.reddit.com/r/gamedev/comments/ylnuj/comment/c5wpkzy/?utm_source=share&utm_medium=web2x&context=3
     */
    TTF_Font *m_Font;

    GLuint m_TextureId;
};

#endif
