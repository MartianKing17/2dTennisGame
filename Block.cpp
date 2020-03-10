//
// Created by maxim on 03.07.2019.
//

#include "Block.h"

Block::Block(ObjectCreater object, GLFWwindow *mainwindow, Shader shader)
        : BaseGameObject(object, mainwindow,shader){}

Block::Block(const Block &other)
    :BaseGameObject(other){}

Block::Block(Block && other)
    :BaseGameObject(other){}

Block & Block::operator =(const Block & other)
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

    return *this;
}

Block & Block::operator =(Block && other) noexcept
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

    return *this;
}

void Block::update()
{
    glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);

    glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    glm::mat4 model=glm::mat4(1.f);
    model=glm::translate(model, glm::vec3(a, b, c));
    model=glm::scale(model, glm::vec3(sx, sy, sz));

    this->worldModel = projection * camera * model;
}


