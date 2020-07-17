//
// Created by maxim on 10.05.2019.
//

#ifndef GAMEGRAPHICLIBRARY_SHADER_H
#define GAMEGRAPHICLIBRARY_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shader
{
    GLuint createShader(const GLchar * shaderSource,GLuint shaderType);
    std::string * readShader(const std::string vertexPath,const std::string fragmentPath);
    GLuint program;
public:
    Shader()= default;
    Shader(const Shader & other)= default;
    Shader(Shader && other)= default;
    GLuint getProgram();
    Shader(const std::string vertexPath,const std::string fragmentPath);
    void operator=(const Shader & other);
    void operator=(Shader && other) noexcept;
    void Use();
    ~Shader()= default;
};

#endif //GAMEGRAPHICLIBRARY_SHADER_H
