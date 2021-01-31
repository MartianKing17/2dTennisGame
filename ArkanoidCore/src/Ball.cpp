//
// Created by maxim on 16.07.2020.
//

#include "../include/Ball.h"

Ball::Ball(Render *renderModel)
        : BaseGameObject(renderModel), m_verticalSpeed(-0.01f), m_horizontalSpeed(0)
{
    auto matValue = this->renderModel->getValue();
    setPosition(matValue);
}

void Ball::update()
{
    MatrixValue matVal = renderModel->getValue();
    matVal.a += m_horizontalSpeed;
    matVal.b += m_verticalSpeed;
    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matVal.a, matVal.b, matVal.c));
    this->model = glm::scale(this->model, glm::vec3(matVal.sx, matVal.sy, matVal.sz));
    renderModel->setValue(matVal);
}

void Ball::setSpeed(float horizontalSpeed, float verticalSpeed)
{
    this->m_horizontalSpeed = horizontalSpeed;
    this->m_verticalSpeed   = verticalSpeed;
}
