#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

#include <GL/glew.h>

#include <util/game_object.h>

class Image final : public Util::GameObject {
public:
    Image();
    ~Image() override;

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
};

#endif
