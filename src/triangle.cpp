#include "triangle.h"

#include <string>

#include "util/loader.h"

Triangle::Triangle() {
    CreateProgram();
    CreateVao();
}

Triangle::~Triangle() {
    glDeleteBuffers(1, &m_VertexBufferId);
    glDeleteBuffers(1, &m_ColorBufferId);
    glDeleteBuffers(1, &m_IndexBufferId);

    glDeleteProgram(m_ProgramId);
}

void Triangle::Update() {
    glUseProgram(m_ProgramId);

    GLint status;
    glValidateProgram(m_ProgramId);
    glGetProgramiv(m_ProgramId, GL_VALIDATE_STATUS, &status);
    if (status != GL_TRUE) {
        int infoLogLength;
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> errMessage(infoLogLength + 1);
        glGetProgramInfoLog(m_ProgramId, infoLogLength, 0, &errMessage[0]);
    }

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferId);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glUseProgram(0);
}

void Triangle::CreateProgram() {
    m_ProgramId = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSource =
        Util::LoadTextFile("../assets/shaders/triangle.vert");
    const GLchar *vertSrcPtr = vertexShaderSource.c_str();

    glShaderSource(vertexShader, 1, &vertSrcPtr, 0);
    glCompileShader(vertexShader);

    GLint status = GL_FALSE;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        int infoLogLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> errMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertexShader, infoLogLength, 0, &errMessage[0]);
    }

    glAttachShader(m_ProgramId, vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderSource =
        Util::LoadTextFile("../assets/shaders/triangle.frag");
    const GLchar *fragSrcPtr = fragmentShaderSource.c_str();

    glShaderSource(fragmentShader, 1, &fragSrcPtr, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        int infoLogLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> errMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShader, infoLogLength, 0, &errMessage[0]);
    }

    glAttachShader(m_ProgramId, fragmentShader);

    glLinkProgram(m_ProgramId);

    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        int infoLogLength;
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> errMessage(infoLogLength + 1);
        glGetProgramInfoLog(m_ProgramId, infoLogLength, 0, &errMessage[0]);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Triangle::CreateVao() {
    std::vector<GLfloat> vertexData = {
        -0.5f, -0.5f, //
        0.5f,  -0.5f, //
        0.0f,  0.5f,  //
    };

    std::vector<GLfloat> colorData = {
        1.0f, 0.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //
        0.0f, 0.0f, 1.0f, //
    };

    std::vector<GLint> indexData = {0, 1, 2};

    glGenBuffers(1, &m_VertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, 2 * vertexData.size() * sizeof(GLfloat),
                 vertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, 3 * colorData.size() * sizeof(GLfloat),
                 colorData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_IndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint),
                 indexData.data(), GL_STATIC_DRAW);
}
