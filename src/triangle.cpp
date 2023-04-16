#include "triangle.h"

#include <string>

#include "util/loader.h"

Triangle::Triangle() {
    CreateProgram();

    CreateVAO();
}

Triangle::~Triangle() {
    glDeleteBuffers(1, &m_VertexBufferID);
    glDeleteBuffers(1, &m_ColorBufferID);
    glDeleteBuffers(1, &m_IndexBufferID);

    glDeleteProgram(m_ProgramID);
}

void Triangle::CreateProgram() {
    m_ProgramID = glCreateProgram();

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

    glAttachShader(m_ProgramID, vertexShader);

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

    glAttachShader(m_ProgramID, fragmentShader);

    glLinkProgram(m_ProgramID);

    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        int infoLogLength;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> errMessage(infoLogLength + 1);
        glGetProgramInfoLog(m_ProgramID, infoLogLength, 0, &errMessage[0]);
    }

    glClearColor(0.f, 0.f, 0.f, 1.f);
}

void Triangle::CreateVAO() {
    m_VertexData = {
        -0.5f, -0.5f, //
        0.5f,  -0.5f, //
        0.f,   0.5f,  //
    };

    m_ColorData = {
        1.0f, 0.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //
        0.0f, 0.0f, 1.0f  //
    };

    m_IndexData = {0, 1, 2};

    glGenBuffers(1, &m_VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, 2 * m_VertexData.size() * sizeof(GLfloat),
                 m_VertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_ColorBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferID);
    glBufferData(GL_ARRAY_BUFFER, 3 * m_ColorData.size() * sizeof(GLfloat),
                 m_ColorData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_IndexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexData.size() * sizeof(GLuint),
                 m_IndexData.data(), GL_STATIC_DRAW);
}

void Triangle::Update() {
    glUseProgram(m_ProgramID);

    GLint status;
    glValidateProgram(m_ProgramID);
    glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &status);
    if (status != GL_TRUE) {
        int infoLogLength;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> errMessage(infoLogLength + 1);
        glGetProgramInfoLog(m_ProgramID, infoLogLength, 0, &errMessage[0]);
    }

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferID);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glUseProgram(0);
}
