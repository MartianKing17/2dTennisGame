//
// Created by maxim on 16.07.2020.
//

#include "Ball.h"

#include <utility>

Ball::Ball(GLFWwindow *mainwindow, RenderModel *renderModel, std::function<bool()> handler)
        : BaseGameObject(mainwindow, renderModel), verticalSpeed(-0.01f), gorizontalSpeed(0), handler(std::move(handler))
{
    auto matValue = this->renderModel->getValues();
    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matValue.a, matValue.b, matValue.c));
    this->model = glm::scale(this->model, glm::vec3(matValue.sx, matValue.sy, matValue.sz));
}

void Ball::update()
{
    MatrixValue matVal = renderModel->getValues();

    if (handler());

    matVal.a += gorizontalSpeed;
    matVal.b += verticalSpeed;

    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matVal.a, matVal.b, matVal.c));
    this->model = glm::scale(this->model, glm::vec3(matVal.sx, matVal.sy, matVal.sz));

    renderModel->setValues(matVal);
}

void Ball::setSpeed(float gorizontalSpeed, float verticalSpeed)
{
    this->gorizontalSpeed = gorizontalSpeed;
    this->verticalSpeed   = verticalSpeed;
}
