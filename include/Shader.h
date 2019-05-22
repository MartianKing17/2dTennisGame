//
// Created by maxim on 10.05.2019.
//

#ifndef GAMEGRAPHICLIBRARY_SHADER_H
#define GAMEGRAPHICLIBRARY_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLEW/include/GL/glew.h>

class Shader
{
    GLuint createShader(const GLchar * shaderSource,GLuint shaderType);
    std::string * readShader(const std::string vertexPath,const std::string fragmentPath);
    GLuint program;
public:
    Shader(const std::string vertexPath,const std::string fragmentPath);

    void Use();
};

#endif //GAMEGRAPHICLIBRARY_SHADER_H
