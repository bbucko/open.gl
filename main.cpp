#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include <fstream>

void checkShaderCompilation(GLuint vertexShader);

std::string readShaderFromFile(char const *fileName);

GLuint compileShader(std::string &vertexSource, auto vertextType);

int main() {
//    createWindow(title, width, height);
//    createOpenGLContext(settings);
//
//    while (windowOpen) {
//        while (event = newEvent())
//            handleEvent(event);
//
//        updateScene();
//
//        drawGraphics();
//        presentGraphics();
//    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_Window *window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();

    float vertices[] = {
            0.0f, 0.5f, // Vertex 1 (X, Y)
            0.5f, -0.5f, // Vertex 2 (X, Y)
            -0.5f, -0.5f  // Vertex 3 (X, Y)
    };

    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    std::string vertexSource = readShaderFromFile("shaders/simple.vert");
    std::string fragmentSource = readShaderFromFile("shaders/simple.frag");

    GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    checkShaderCompilation(vertexShader);

    GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
    checkShaderCompilation(fragmentShader);

    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) break;
        }

        SDL_GL_SwapWindow(window);
    }


    SDL_GL_DeleteContext(context);
    SDL_Quit();

    return 0;
}

GLuint compileShader(std::string &vertexSource, auto vertextType) {
    GLuint vertexShader = glCreateShader(vertextType);
    glShaderSource(vertexShader, 1, (const GLchar **) &vertexSource, NULL);
    glCompileShader(vertexShader);
    return vertexShader;
}

std::string readShaderFromFile(char const *fileName) {
    std::ifstream simpleFrag(fileName);
    std::string vertexSource((std::istreambuf_iterator<char>(simpleFrag)), std::istreambuf_iterator<char>());
    return vertexSource;
}

void checkShaderCompilation(GLuint vertexShader) {
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
        std::cout << buffer << std::endl;
    }
}