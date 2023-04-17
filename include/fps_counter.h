#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <vector>

#include <GL/glew.h>

#include <SDL_ttf.h>

#include <util/game_object.h>

class FpsCounter : public Util::GameObject {
public:
    FpsCounter();
    ~FpsCounter() override;

    void Update() override;

private:
    void CreateProgram();
    void CreateVao();
    void CreateTexture();

private:
    GLuint m_ProgramId;

    GLuint m_VertexBufferId;
    GLuint m_UvBufferId;
    GLuint m_IndexBufferId;

    unsigned int m_IndexCount;

    GLuint m_TextureId;

    /**
     * Probably not the most performant way to do it
     * https://www.reddit.com/r/gamedev/comments/ylnuj/comment/c5wpkzy/?utm_source=share&utm_medium=web2x&context=3
     */
    TTF_Font *m_Font;
};

#endif
