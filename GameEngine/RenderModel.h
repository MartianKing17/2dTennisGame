//
// Created by maxim on 15.07.2020.
//

#ifndef ARKANOID_RENDERMODEL_H
#define ARKANOID_RENDERMODEL_H
#include <array>
#include "include/SOIL.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include "include/glfw3.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>

struct MatrixValue
{
    float a, b, c;
    float sx, sy, sz;
};

class RenderModel
{
    std::pair<double,double> objProjCoor;
    GLint modelCoor;
    float a,b,c; //Object matrix + a = x + a, Obj. mat. + b = y + b, Obj. mat. + c = z + c
    float sx,sy,sz;// Object matrix * sx = x * sx, Obj. mat. * sy = y * sy, Obj. mat. * sz = z * sz
    GLuint vbo, vao, ebo;
    GLuint texture;
    Shader shader;
    GLFWwindow * window;
    glm::mat4 worldView;
    glm::mat4 model;
    void initializateVao();
    void initializateVbo();
    void initializateEbo();
public:
    RenderModel() = default;
    RenderModel(MatrixValue matValue, GLFWwindow *window, Shader shader, glm::mat4 worldView, std::string textureFileName);
    RenderModel(const RenderModel & other);
    RenderModel(RenderModel && other);
    RenderModel & operator =(const RenderModel & other);
    RenderModel & operator =(RenderModel && other) noexcept;
    void createTexture(std::string texName);
    void setValues(MatrixValue matrixValue);
    MatrixValue getValues();
    void render(glm::mat4 model); //RenderModel position place and drawing paint
    virtual ~RenderModel();
};


#endif //ARKANOID_RENDERMODEL_H
