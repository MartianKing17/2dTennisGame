//
// Created by maxim on 11.07.2019.
//

#ifndef INC_2DTENNISGAME_BASEGAMEOBJECT_H
#define INC_2DTENNISGAME_BASEGAMEOBJECT_H

#include <array>
#include "include/Shader.h"
#include "include/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "ObjectCreater.h"
#include <iostream>
#include <vector>
#include <utility>

class BaseGameObject
{
protected:
    std::array<std::pair<double,double>, 3> * obj_coordinate_projection;
    GLint modelCoor;
    float cx, cy, radius; //Central x, central,y and radius
    float a,b,c; //Object matrix + a = x + a, Obj. mat. + b = y + b, Obj. mat. + c = z + c
    float sx,sy,sz;// Object matrix * sx = x * sx, Obj. mat. * sy = y * sy, Obj. mat. * sz = z * sz
    GLuint vbo, vao, ebo;
    GLuint texture;
    Shader shader;
    GLFWwindow * window;
    bool value;
    glm::mat4 model;
public:
    BaseGameObject();
    BaseGameObject(ObjectCreater object, GLFWwindow *mainwindow, Shader shader);
    BaseGameObject(const BaseGameObject & other);
    BaseGameObject(BaseGameObject && other);
    BaseGameObject & operator =(const BaseGameObject & other);
    BaseGameObject & operator =(BaseGameObject && other) noexcept;
    void set_matrix_translate(float a, float b, float c);
    void set_matrix_scale(float sx, float sy, float sz);
    void render(); //Render position place and drawing paint
    virtual void update() = 0; //Update position data
    float getVerticalPlace();
    float getGorizontalPlace();
    float getRadius();
    std::array<std::pair<double, double>, 3> return_position();
    virtual ~BaseGameObject();
};


#endif //INC_2DTENNISGAME_BASEGAMEOBJECT_H
