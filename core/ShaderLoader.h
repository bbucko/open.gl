#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include "../include.h"

class ShaderLoader {
private:
    void checkCompilationStatus(GLuint shader);
    void checkLinkStatus(GLuint shader);

public:
    GLuint loadShader(GLenum shaderTye, char const *fileName);

    GLuint createProgram(char const *vertexShaderFilename, char const *fragmentShaderFilename);

};