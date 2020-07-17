//
// Created by maxim on 16.07.2020.
//

#include "Block.h"

Block::Block(GLFWwindow *mainwindow, RenderModel *renderModel)
        : BaseGameObject(mainwindow, renderModel)
{
    auto matValue = this->renderModel->getValues();
    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matValue.a, matValue.b, matValue.c));
    this->model = glm::scale(this->model, glm::vec3(matValue.sx, matValue.sy, matValue.sz));
}

Block::Block(const Block &other)
        :BaseGameObject(other){}

Block::Block(Block && other)
        :BaseGameObject(other){}

Block & Block::operator =(const Block & other)
{
    this->value=other.value;
    this->window=other.window;
    this->renderModel = other.renderModel;
    this->model = other.model;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;

    return *this;
}

Block & Block::operator =(Block && other) noexcept
{
    this->value=other.value;
    this->window=other.window;
    this->renderModel = other.renderModel;
    this->model = other.model;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;

    other.value=false;
    other.window= nullptr;
    other.renderModel = nullptr;
    other.model = glm::mat4(1.f);
    other.cx = 0.f;
    other.cy = 0.f;
    other.radius = 0.f;

    return *this;
}

bool Block::operator==(const Block &other) const
{
    /*
    if (this->model != other.model)
        return false;
    */
    return true;
}

bool Block::operator!=(const Block &other) const
{
    return !operator==(other);
}

void Block::update()
{
    MatrixValue matVal = renderModel->getValues();
    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matVal.a, matVal.b, matVal.c));
    this->model = glm::scale(this->model, glm::vec3(matVal.sx, matVal.sy, matVal.sz));
}
