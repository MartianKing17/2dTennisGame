//
// Created by maxim on 10.05.2019.
//

#ifndef GAMEGRAPHICLIBRARY_SHADER_H
#define GAMEGRAPHICLIBRARY_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLEW/glew/include/GL/glew.h>

class Shader
{
    GLuint createShader(const GLchar * shaderSource,GLuint shaderType);
    std::string * readShader(const std::string vertexPath,const std::string fragmentPath);

public:
    GLuint program;
    Shader()= default;
    Shader(const Shader & other)= default;
    Shader(Shader && other)= default;
    Shader(const std::string vertexPath,const std::string fragmentPath);
    Shader &operator=(const Shader & other)= default;
    Shader &operator=(Shader && other)= default;
    void Use();
    ~Shader()= default;
};

#endif //GAMEGRAPHICLIBRARY_SHADER_H
