//
// Created by maxim on 16.07.2020.
//

#include "../include/BaseGameObject.h"

BaseGameObject::BaseGameObject(Render *renderModel)
        : value(false), renderModel(renderModel)
{}

BaseGameObject::BaseGameObject(const BaseGameObject &other)
{
    this->value = other.value;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;
    this->model = other.model;
    this->renderModel = other.renderModel;
}

BaseGameObject::BaseGameObject(BaseGameObject &&other)
{
    this->value=other.value;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;
    this->model = other.model;
    this->renderModel = other.renderModel;
    other.value=false;
    other.cx = 0;
    other.cy = 0;
    other.radius = 0;
    other.model = {};
    other.renderModel = nullptr;
}

BaseGameObject& BaseGameObject::operator=(const BaseGameObject &other)
{
    this->value = other.value;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;
    this->model = other.model;
    this->renderModel = other.renderModel;
    return *this;
}

BaseGameObject& BaseGameObject::operator=(BaseGameObject &&other) noexcept
{
    this->value = other.value;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;
    this->model = other.model;
    this->renderModel = other.renderModel;
    other.value=false;
    other.cx = 0;
    other.cy = 0;
    other.radius = 0;
    other.model = {};
    other.renderModel = nullptr;
    return *this;
}

float BaseGameObject::getVerticalPlace() const
{
    return this->cy - this->radius;
}

float BaseGameObject::getGorizontalPlace() const
{
    return this->cx + this->radius;
}

float BaseGameObject::getRadius() const
{
    return this->radius;
}

void BaseGameObject::setPosition(MatrixValue matrixValue)
{
    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matrixValue.a, matrixValue.b, matrixValue.c));
    this->model = glm::scale(this->model, glm::vec3(matrixValue.sx, matrixValue.sy, matrixValue.sz));
    this->renderModel->setValue(matrixValue);
}

glm::mat4 BaseGameObject::getPosition()
{
    return this->model;
}

void BaseGameObject::render()
{
    this->renderModel->render(this->model);
}

void BaseGameObject::update()
{
    return;
}

BaseGameObject::~BaseGameObject()
{
    delete renderModel;
}
