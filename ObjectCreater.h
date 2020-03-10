//
// Created by maxim on 02.08.2019.
//

#ifndef INC_2DTENNISGAME_OBJECTCREATER_H
#define INC_2DTENNISGAME_OBJECTCREATER_H

#include <array>
#include "include/Shader.h"
#include "include/glfw3.h"
#include <iostream>
#include "include/SOIL.h"
#include <vector>
#include <string>

class ObjectCreater
{
    GLuint vbo, vao, ebo;
    GLuint texture;
    float a,b,c; //Object matrix + a = x + a, Obj. mat. + b = y + b, Obj. mat. + c = z + c
    float sx,sy,sz;// Object matrix * sx = x * sx, Obj. mat. * sy = y * sy, Obj. mat. * sz = z * sz
    GLfloat vertices[32];
    GLint indices[6];
    std::string texName;
    void createTexture(std::string data);
    void initializateVao();
    void initializateVbo();
    void initializateEbo();
    bool init;
public:
    ObjectCreater()= default;
    ObjectCreater(std::vector<GLfloat> startObjectPosition, std::string texName);
    ObjectCreater(const ObjectCreater &other);
    ObjectCreater(ObjectCreater &&other) noexcept;
    ObjectCreater & operator=(const ObjectCreater &other);
    ObjectCreater & operator=(ObjectCreater &&other) noexcept;
    void initializate();
    bool isInitializate();
    void setMatrixTranslate(float a, float b, float c);
    void setMatrixScale(float sx, float sy, float sz);
    float * getMatrixTranslate();
    float * getMatrixScale();
    std::array<double, 3> returnModelLocCoor();
    std::array<GLuint,4> returnData();
    ~ObjectCreater()= default;
};


#endif //INC_2DTENNISGAME_OBJECTCREATER_H
