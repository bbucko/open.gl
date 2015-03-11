#include <SDL.h>
#include <GL/glew.h>
#include "include.h"
#include "core/ShaderLoader.h"


//SDL Context
SDL_Window *window;
SDL_GLContext context;

void printError();

void initOpenGLContext();

void initWindow() {
    LOG("Initializing OpenGL and SDL");
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
}

void initOpenGLContext() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    context = SDL_GL_CreateContext(window);

    LOG("Initialize GLEW");
    glewExperimental = GL_TRUE;
    glewInit();
}

ShaderLoader shaderLoader;

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

    initWindow();
    initOpenGLContext();

    LOG("Create Vertex Array Object");
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    LOG("Create a Vertex Buffer Object and copy the vertex data to it");
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer

    GLfloat vertices[] = {
            -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Top-left
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Top-right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
    };


    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    LOG("Create a Element Buffer Object and set the order");
    GLuint ebo;
    glGenBuffers(1, &ebo);
    GLuint elements[] = {
            0, 1, 2,
//            0, 1, 2,
            2, 3, 0
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


    LOG("Link the vertex and fragment shader into a shader program");
    GLuint shaderProgram = shaderLoader.createProgram("shaders/simple.vert", "shaders/simple.frag");
    glUseProgram(shaderProgram);
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    LOG("Specify the layout of the vertex data");
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (2 * sizeof(float)));


    LOG("Specify uniforms");
    GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

    printError();

    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) break;
        }

        // Set the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle from the 3 vertices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        printError();

        SDL_GL_SwapWindow(window);
    }

    glDeleteProgram(shaderProgram);
//    glDeleteShader(fragmentShader);
//    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);


    SDL_GL_DeleteContext(context);
    SDL_Quit();
}

void printError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        ERROR("OpenGL error: %i", err);
    }
}
