//
// Created by maxim on 11.07.2019.
//

#include <vector>
#include "BaseGameObject.h"

BaseGameObject::BaseGameObject()
{
    vbo=0, vao=0, ebo=0;
    texture=0;
    shader=Shader();
    modelCoor = glGetUniformLocation(shader.program,"model");
    window= nullptr;
    value=false;
    obj_coordinate_projection = nullptr;
}

BaseGameObject::BaseGameObject(ObjectCreater object, GLFWwindow *mainwindow, Shader shader)
                               :window(mainwindow),shader(shader),value(false),modelCoor(glGetUniformLocation(shader.program,"model"))
{
    if(!object.isInitializate())
    {
        object.initializate();
    }

    auto data= object.return_data();

    vao=data.at(0);
    vbo=data.at(1);
    ebo=data.at(2);

    texture=data.at(3);
    float * matrix = object.get_matrix_translate();
    this->a = matrix[0];
    this->b = matrix[1];
    this->c = matrix[2];
    delete[] matrix;
    matrix = nullptr;

    matrix = object.get_matrix_scale();
    this->sx = matrix[0];
    this->sy = matrix[1];
    this->sz = matrix[2];
    delete[] matrix;
    matrix = nullptr;

    obj_coordinate_projection = object.return_model_coor();
}

BaseGameObject::BaseGameObject(const BaseGameObject &other)
{
    this->vao=other.vao;
    this->vbo=other.vbo;
    this->ebo=other.ebo;

    this->texture=other.texture;
    this->shader=other.shader;
    this->value=other.value;

    this->window=other.window;
    this->modelCoor = other.modelCoor;
    this->obj_coordinate_projection = other.obj_coordinate_projection;

    this->a = other.a;
    this->b = other.b;
    this->c = other.c;

    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;
}

BaseGameObject::BaseGameObject(BaseGameObject &&other)
{
    this->vao=other.vao;
    this->vbo=other.vbo;
    this->ebo=other.ebo;

    this->texture=other.texture;
    this->shader=other.shader;
    this->value=other.value;

    this->window=other.window;
    this->modelCoor = other.modelCoor;
    this->obj_coordinate_projection = other.obj_coordinate_projection;

    this->a = other.a;
    this->b = other.b;
    this->c = other.c;

    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;

    other.vao=0;
    other.vbo=0;
    other.ebo=0;

    other.texture=0;
    //other.shader= nullptr;
    other.value=false;

    other.window= nullptr;
    other.modelCoor = 0;
    other.obj_coordinate_projection = nullptr;

    other.a = 0;
    other.b = 0;
    other.c = 0;

    other.sx = 0;
    other.sy = 0;
    other.sz = 0;
}

BaseGameObject& BaseGameObject::operator=(const BaseGameObject &other)
{
    this->vao=other.vao;
    this->vbo=other.vbo;
    this->ebo=other.ebo;

    this->texture=other.texture;
    this->shader=other.shader;
    this->value=other.value;

    this->window=other.window;
    this->modelCoor = other.modelCoor;
    this->obj_coordinate_projection = other.obj_coordinate_projection;

    this->a = other.a;
    this->b = other.b;
    this->c = other.c;

    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;

    return *this;
}

BaseGameObject& BaseGameObject::operator=(BaseGameObject &&other) noexcept
{
    this->vao=other.vao;
    this->vbo=other.vbo;
    this->ebo=other.ebo;

    this->texture=other.texture;
    this->shader=other.shader;
    this->value=other.value;

    this->window=other.window;
    this->modelCoor = other.modelCoor;
    this->obj_coordinate_projection = other.obj_coordinate_projection;

    this->a = other.a;
    this->b = other.b;
    this->c = other.c;

    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;

    other.vao=0;
    other.vbo=0;
    other.ebo=0;

    other.texture=0;
    //other.shader= nullptr;
    other.value=false;

    other.window= nullptr;
    other.modelCoor = 0;
    other.obj_coordinate_projection = nullptr;

    other.a = 0;
    other.b = 0;
    other.c = 0;

    other.sx = 0;
    other.sy = 0;
    other.sz = 0;

    return *this;
}

void BaseGameObject::set_matrix_translate(float a, float b, float c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

void BaseGameObject::set_matrix_scale(float sx, float sy, float sz)
{
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}

float BaseGameObject::getVerticalPlace()
{
    return this->cy;
}

float BaseGameObject::getGorizontalPlace()
{
    return this->cx;
}

float BaseGameObject::getRadius()
{
    return this->radius;
}

void BaseGameObject::render()
{
    glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);

    glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    glm::mat4 model_mat4=glm::mat4(1.f);
    model_mat4=glm::translate(model_mat4, glm::vec3(a, b, c));
    model_mat4=glm::scale(model_mat4, glm::vec3(sx, sy, sz));

    this->model = projection * camera * model_mat4;
    glUniformMatrix4fv(this->modelCoor,1,GL_FALSE,glm::value_ptr(model));
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader.Use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D,0);
    glBindVertexArray(0);
    glDisable(GL_BLEND);
}

std::array<std::pair<double, double>, 3> BaseGameObject::return_position()
{
    const double x = model[0][0];
    const double y = model[1][1];

    for (int i = 0; i < obj_coordinate_projection->size(); ++i)
    {
       obj_coordinate_projection->at(i).first *= x;
       obj_coordinate_projection->at(i).second *= y;
    }

    return *obj_coordinate_projection;
}

BaseGameObject::~BaseGameObject()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    delete obj_coordinate_projection;
}