#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

#include <GL/glew.h>

#include "util/game_object.h"

class Triangle final : public Util::GameObject {
public:
    Triangle();
    ~Triangle() override;

    void Update() override;

private:
    void CreateProgram();
    void CreateVao();

private:
    GLuint m_ProgramId;

    GLuint m_VertexBufferId;
    GLuint m_ColorBufferId;
    GLuint m_IndexBufferId;
};

#endif
