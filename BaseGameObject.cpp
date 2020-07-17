//
// Created by maxim on 16.07.2020.
//

#include "BaseGameObject.h"

BaseGameObject::BaseGameObject(GLFWwindow *mainWindow, RenderModel *renderModel)
        : window(mainWindow),value(false), renderModel(renderModel)
{}

BaseGameObject::BaseGameObject(const BaseGameObject &other)
{
    this->value=other.value;
    this->window=other.window;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;
}

BaseGameObject::BaseGameObject(BaseGameObject &&other)
{
    this->value=other.value;
    this->window=other.window;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;

    other.value=false;
    other.window= nullptr;
    other.cx = 0;
    other.cy = 0;
    other.radius = 0;
}

BaseGameObject& BaseGameObject::operator=(const BaseGameObject &other)
{
    this->value=other.value;
    this->window=other.window;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;

    return *this;
}

BaseGameObject& BaseGameObject::operator=(BaseGameObject &&other) noexcept
{
    this->value=other.value;
    this->window=other.window;
    this->cx = other.cx;
    this->cy = other.cy;
    this->radius = other.radius;

    other.value=false;
    other.window= nullptr;
    other.cx = 0;
    other.cy = 0;
    other.radius = 0;

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

void BaseGameObject::render()
{
    this->renderModel->render(this->model);
}

void BaseGameObject::update()
{
    return;
}

BaseGameObject::~BaseGameObject()
{}
