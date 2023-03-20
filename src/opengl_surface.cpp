#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

    SDL_Window *window = SDL_CreateWindow(   //
        "OpenGL",                            //
        SDL_WINDOWPOS_UNDEFINED,             //
        SDL_WINDOWPOS_UNDEFINED,             //
        1280,                                //
        720,                                 //
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN //
    );

    SDL_GLContext context = SDL_GL_CreateContext(window);

    const GLenum status = glewInit();

    GLuint programID = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar *vertexShaderSource[] = {
        "#version 140\n"                                                   //
        "in vec2 LVertexPos2D;\n"                                          //
        "in vec3 color;\n"                                                 //
        "out vec3 vertexColor;\n"                                          //
        "void main() {\n"                                                  //
        "    gl_Position = vec4(LVertexPos2D.x, LVertexPos2D.y, 0, 1 );\n" //
        "    vertexColor = color;\n"                                       //
        "}\n"                                                              //
    };

    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glAttachShader(programID, vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar *fragmentShaderSource[] = {
        "#version 140\n"                            //
        "in vec3 vertexColor;\n"                    //
        "out vec4 LFragment;\n"                     //
        "void main() {\n"                           //
        "    LFragment = vec4(vertexColor, 1.0);\n" //
        "}\n"                                       //
    };

    glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glAttachShader(programID, fragmentShader);

    glLinkProgram(programID);

    GLint vertexPos2DLocation = glGetAttribLocation(programID, "LVertexPos2D");
    GLint colorDataLocation = glGetAttribLocation(programID, "color");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    std::vector<GLfloat> vertexData = {
        -0.5f, -0.5f, //
        0.5f,  -0.5f, //
        0.f,   0.5f,  //
    };

    std::vector<GLfloat> colorData = {
        1.0f, 0.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //
        0.0f, 0.0f, 1.0f  //
    };

    std::vector<GLuint> indexData = {0, 1, 2};

    GLuint vbo;
    GLuint cbo;
    GLuint ibo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * vertexData.size() * sizeof(GLfloat),
                 vertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * colorData.size() * sizeof(GLfloat),
                 colorData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint),
                 indexData.data(), GL_STATIC_DRAW);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Render quad
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);

        glEnableVertexAttribArray(vertexPos2DLocation);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE,
                              2 * sizeof(GLfloat), NULL);

        glEnableVertexAttribArray(colorDataLocation);
        glBindBuffer(GL_ARRAY_BUFFER, cbo);
        glVertexAttribPointer(colorDataLocation, 3, GL_FLOAT, GL_FALSE,
                              3 * sizeof(GLfloat), NULL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, NULL);

        glUseProgram(NULL);

        SDL_GL_SwapWindow(window);
    }

    glDeleteProgram(programID);

    SDL_DestroyWindow(window);
    SDL_Quit();
}
