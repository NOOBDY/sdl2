#include "fps_counter.h"

#include <iostream>

#include <fmt/core.h>

#include "util/time.h"
#include "util/loader.h"

FpsCounter::FpsCounter() {
    std::string filepath = "../assets/fonts/lazy.ttf";

    m_Font = TTF_OpenFont(filepath.c_str(), 12);

    if (!m_Font) {
        std::cout << fmt::format("Failed to load font: '{}'\n", filepath);
    }

    CreateProgram();
    CreateVao();
    CreateTexture();
}

FpsCounter::~FpsCounter() {
    glDeleteBuffers(1, &m_VertexBufferId);
    glDeleteBuffers(1, &m_UvBufferId);
    glDeleteBuffers(1, &m_IndexBufferId);

    glDeleteProgram(m_ProgramId);

    glDeleteTextures(1, &m_TextureId);

    TTF_CloseFont(m_Font);
}

void FpsCounter::Update() {
    std::string fpsText =
        fmt::format("{}", 1.0f / Util::Time::GetDeltaTime()).c_str();
    SDL_Surface *surface =
        TTF_RenderText_Solid(m_Font, fpsText.c_str(), {1, 1, 1});

    if (!surface) {
        std::cout << "Failed to render text surface\n";
        std::cout << TTF_GetError() << "\n";
        return;
    }

    unsigned int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
    std::cout << fmt::format("{:d}\n", surface->format->BytesPerPixel);

    if (!surface) {
        std::cout << "Unable to render text surface\n";
        std::cout << TTF_GetError() << "\n";
    }

    glUseProgram(m_ProgramId);

    GLuint location = glGetUniformLocation(m_ProgramId, "text");
    glUniform1i(location, 0);

    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode,
                 GL_UNSIGNED_BYTE, surface->pixels);

    GLint status = GL_FALSE;
    glValidateProgram(m_ProgramId);
    glGetProgramiv(m_ProgramId, GL_VALIDATE_STATUS, &status);
    if (status != GL_TRUE) {
        int infoLogLength;
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> errMessage(infoLogLength + 1);
        glGetProgramInfoLog(m_ProgramId, infoLogLength, 0, &errMessage[0]);

        for (const auto &msg : errMessage)
            std::cout << msg << "\n";
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_UvBufferId);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

    glUseProgram(0);

    SDL_FreeSurface(surface);
}

void FpsCounter::CreateProgram() {
    m_ProgramId = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSource =
        Util::LoadTextFile("../assets/shaders/fps_counter.vert");
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

        for (const auto &msg : errMessage)
            std::cout << msg << "\n";
    }

    glAttachShader(m_ProgramId, vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderSource =
        Util::LoadTextFile("../assets/shaders/fps_counter.frag");
    const GLchar *fragSrcPtr = fragmentShaderSource.c_str();

    glShaderSource(fragmentShader, 1, &fragSrcPtr, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        int infoLogLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> errMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShader, infoLogLength, 0, &errMessage[0]);

        for (const auto &msg : errMessage)
            std::cout << msg << "\n";
    }

    glAttachShader(m_ProgramId, fragmentShader);

    glLinkProgram(m_ProgramId);

    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        int infoLogLength;
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> errMessage(infoLogLength + 1);
        glGetProgramInfoLog(m_ProgramId, infoLogLength, 0, &errMessage[0]);

        for (const auto &msg : errMessage)
            std::cout << msg << "\n";
    }
}

void FpsCounter::CreateVao() {
    std::vector<GLfloat> vertexData = {
        -1.0f, -1.0f, //
        -0.5f, -1.0f, //
        -1.0f, -0.5f, //
        -0.5f, -0.5f, //
    };

    std::vector<GLfloat> uvData = {
        0.0f, 0.0f, //
        1.0f, 0.0f, //
        0.0f, 1.0f, //
        1.0f, 1.0f, //
    };

    std::vector<GLint> indexData = {
        0, 1, 2, //
        2, 1, 3, //
    };

    glGenBuffers(1, &m_VertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, 2 * vertexData.size() * sizeof(GLfloat),
                 vertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_UvBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_UvBufferId);
    glBufferData(GL_ARRAY_BUFFER, 2 * uvData.size() * sizeof(GLfloat),
                 uvData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_IndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint),
                 indexData.data(), GL_STATIC_DRAW);

    m_IndexCount = indexData.size();
}

void FpsCounter::CreateTexture() {
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
