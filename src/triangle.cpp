#include "triangle.h"

#include "util/vector.h"

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

    const GLchar *vertexShaderSource[] = {
        "#version 330 core\n"                                              //
        "in vec2 LVertexPos2D;\n"                                          //
        "in vec3 color;\n"                                                 //
        "out vec3 vertexColor;\n"                                          //
        "void main() {\n"                                                  //
        "    gl_Position = vec4(LVertexPos2D.x, LVertexPos2D.y, 0, 1 );\n" //
        "    vertexColor = color;\n"                                       //
        "}\n"                                                              //
    };

    glShaderSource(vertexShader, 1, vertexShaderSource, 0);
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

    const GLchar *fragmentShaderSource[] = {
        "#version 330 core\n"                       //
        "in vec3 vertexColor;\n"                    //
        "out vec4 LFragment;\n"                     //
        "void main() {\n"                           //
        "    LFragment = vec4(vertexColor, 1.0);\n" //
        "}\n"                                       //
    };

    glShaderSource(fragmentShader, 1, fragmentShaderSource, 0);
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

    m_VertexDataLocation = glGetAttribLocation(m_ProgramID, "LVertexPos2D");
    m_ColorDataLocation = glGetAttribLocation(m_ProgramID, "color");

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

void Triangle::OnUpdate() {
    glClear(GL_COLOR_BUFFER_BIT);

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

    glEnableVertexAttribArray(m_VertexDataLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glVertexAttribPointer(m_VertexDataLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(m_ColorDataLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferID);
    glVertexAttribPointer(m_ColorDataLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glUseProgram(0);
}
