#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

#include <glad/gl.h>

#include "util/game_object.h"

class Triangle final : public Util::GameObject {
public:
    Triangle();
    ~Triangle() override;

    void OnUpdate() override;

private:
    void CreateProgram();
    void CreateVAO();

private:
    GLuint m_ProgramID;

    std::vector<GLfloat> m_VertexData;
    std::vector<GLfloat> m_ColorData;
    std::vector<GLint> m_IndexData;

    GLuint m_VertexBufferID;
    GLuint m_ColorBufferID;
    GLuint m_IndexBufferID;
};

#endif
