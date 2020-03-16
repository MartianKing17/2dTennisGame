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
}

BaseGameObject::BaseGameObject(ObjectCreater object, GLFWwindow *mainWindow, Shader shader)
                               : window(mainWindow), shader(shader), value(false), modelCoor(glGetUniformLocation(shader.program, "model"))
{
    if(!object.isInitializate())
    {
        object.initializate();
    }

    auto data= object.returnData();

    vao=data.at(0);
    vbo=data.at(1);
    ebo=data.at(2);

    texture=data.at(3);
    float * matrix = object.getMatrixTranslate();
    this->a = matrix[0];
    this->b = matrix[1];
    this->c = matrix[2];
    delete[] matrix;
    matrix = nullptr;

    matrix = object.getMatrixScale();
    this->sx = matrix[0];
    this->sy = matrix[1];
    this->sz = matrix[2];
    delete[] matrix;
    matrix = nullptr;

    auto arrModelLocCoor = object.returnModelLocCoor();
    objProjCoor = {arrModelLocCoor.at(0), arrModelLocCoor.at(1)};
    this->radius = arrModelLocCoor.at(2);

    glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);

    glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    glm::mat4 model=glm::mat4(1.f);
    model=glm::translate(model, glm::vec3(a, b, c));
    model=glm::scale(model, glm::vec3(sx, sy, sz));

    worldModel = projection * camera * model;

    cx = (worldModel[0][0] + worldModel[3][0]) * (float)objProjCoor.first;
    cy = (worldModel[1][1] + worldModel[3][1]) * (float)objProjCoor.second;
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
    this->objProjCoor = other.objProjCoor;

    this->a = other.a;
    this->b = other.b;
    this->c = other.c;

    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;

    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;

    this->worldModel = other.worldModel;
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
    this->objProjCoor = other.objProjCoor;

    this->a = other.a;
    this->b = other.b;
    this->c = other.c;

    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;

    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;

    this->worldModel = other.worldModel;

    other.vao=0;
    other.vbo=0;
    other.ebo=0;

    other.texture=0;
    //other.shader= nullptr;
    other.value=false;

    other.window= nullptr;
    other.modelCoor = 0;

    other.a = 0;
    other.b = 0;
    other.c = 0;

    other.sx = 0;
    other.sy = 0;
    other.sz = 0;

    other.cx = 0;
    other.cy = 0;
    other.radius = 0;

    other.worldModel = glm::mat4(0.);
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
    this->objProjCoor = other.objProjCoor;

    this->a = other.a;
    this->b = other.b;
    this->c = other.c;

    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;

    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;

    this->worldModel = other.worldModel;

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
    this->objProjCoor = other.objProjCoor;

    this->a = other.a;
    this->b = other.b;
    this->c = other.c;

    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;

    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;

    other.vao=0;
    other.vbo=0;
    other.ebo=0;

    other.texture=0;
    //other.shader= nullptr;
    other.value=false;

    other.window= nullptr;
    other.modelCoor = 0;

    other.a = 0;
    other.b = 0;
    other.c = 0;

    other.sx = 0;
    other.sy = 0;
    other.sz = 0;

    other.cx = 0;
    other.cy = 0;
    other.radius = 0;

    other.worldModel = glm::mat4(0.);

    return *this;
}

void BaseGameObject::setMatrixTranslate(float a, float b, float c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

void BaseGameObject::setMatrixScale(float sx, float sy, float sz)
{
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}

float BaseGameObject::getVerticalPlace()
{
    return this->cy - this->radius;
}

float BaseGameObject::getGorizontalPlace()
{
    return this->cx + this->radius;
}

float BaseGameObject::getRadius()
{
    return this->radius;
}

void BaseGameObject::render()
{

   /* glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);

    glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    glm::mat4 model=glm::mat4(1.f);
    model=glm::translate(model, glm::vec3(a, b, c));
    model=glm::scale(model, glm::vec3(sx, sy, sz));

    this->worldModel = projection * camera * model;*/
    glUniformMatrix4fv(this->modelCoor,1,GL_FALSE,glm::value_ptr(worldModel));
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

BaseGameObject::~BaseGameObject()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}