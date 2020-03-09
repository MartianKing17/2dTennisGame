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
    this->obj_coordinate_projection = other.obj_coordinate_projection;

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

void Block::update()
{}


