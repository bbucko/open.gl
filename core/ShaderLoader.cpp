#include <GL/glew.h>
#include "ShaderLoader.h"

GLuint ShaderLoader::loadShader(GLenum shaderTye, char const *fileName) {
    std::ifstream shaderSource(fileName);
    std::string vertexSource((std::istreambuf_iterator<char>(shaderSource)), std::istreambuf_iterator<char>());

    GLuint shader = glCreateShader(shaderTye);

    //Shader, count, source, length
    glShaderSource(shader, 1, (const GLchar **) &vertexSource, NULL);
    glCompileShader(shader);
    checkCompilationStatus(shader);

    return shader;
}

void ShaderLoader::checkLinkStatus(GLuint program) {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetProgramInfoLog(program, 512, NULL, buffer);
        ERROR(buffer);
    } else {
        LOG("Linking of program %i OK", program);
    }
}

void ShaderLoader::checkCompilationStatus(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        ERROR(buffer);
    } else {
        LOG("Compilation of shader %i OK", shader);
    }
}

GLuint ShaderLoader::createProgram(char const *vertexShaderFilename, char const *fragmentShaderFilename) {
    GLuint shaderProgram = glCreateProgram();

    LOG("Create and compile the vertex shader");
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderFilename);
    glAttachShader(shaderProgram, vertexShader);

    LOG("Create and compile the fragment shader");
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    checkLinkStatus(shaderProgram);
    return shaderProgram;
}
