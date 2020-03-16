//
// Created by maxim on 10.05.2019.
//

#include "Shader.h"

using namespace std;

Shader::Shader(const std::string vertexPath,const std::string fragmentPath)
{
    string * shaders;

    try
    {
        shaders=readShader(vertexPath,fragmentPath);
    }

    catch(ifstream::failure e)
    {
        cout<<"Error::SHADER::FILE_NOT_SUCCESFULLY_READ"<<endl;
    }

    GLuint vertexShader=createShader(shaders[0].c_str(),GL_VERTEX_SHADER),fragmentShader=createShader(shaders[1].c_str(),GL_FRAGMENT_SHADER);

    this->program=glCreateProgram();

    glAttachShader(this->program,vertexShader);
    glAttachShader(this->program,fragmentShader);
    glLinkProgram(this->program);

    GLint success;
    GLchar infoLog[512];

    glGetProgramiv(this->program,GL_LINK_STATUS,&success);

    if(!success)
    {
        glGetProgramInfoLog(this->program,512,NULL,infoLog);
        cout<<infoLog<<endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::string* Shader::readShader(const std::string vertexPath, const std::string fragmentPath)
{
    string * shaders= new string[2]();
    ifstream vShaderFile;
    ifstream fShaderFile;
    stringstream vShaderStream,fShaderStream;

    vShaderFile.exceptions(ifstream::badbit);
    fShaderFile.exceptions(ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        vShaderStream<<vShaderFile.rdbuf();
        fShaderStream<<fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        shaders[0]=vShaderStream.str();
        shaders[1]=fShaderStream.str();
    }
    catch (ifstream::failure e)
    {
        throw e;
    }

    return shaders;
}

GLuint Shader::createShader(const GLchar * shaderSource,GLuint shaderType)
{
    GLuint shader=glCreateShader(shaderType);
    glShaderSource(shader,1,&shaderSource,NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);

    if(!success)
    {
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        cout<<infoLog<<endl;
    }

    return shader;
}


void Shader::Use()
{
    glUseProgram(this->program);
}