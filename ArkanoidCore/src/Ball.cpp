//
// Created by maxim on 16.07.2020.
//

#include "../include/Ball.h"

Ball::Ball(std::unique_ptr<Render> &&renderModel)
        : BaseGameObject(std::move(renderModel)), m_verticalSpeed(-0.01f), m_horizontalSpeed(0)
{
    auto matValue = m_renderModel->getValue();
    setPosition(matValue);
}

void Ball::update()
{
    MatrixValue matVal = m_renderModel->getValue();
    matVal.a += m_horizontalSpeed;
    matVal.b += m_verticalSpeed;
    setPosition(matVal);
}

void Ball::setSpeed(float horizontalSpeed, float verticalSpeed)
{
    m_horizontalSpeed = horizontalSpeed;
    m_verticalSpeed   = verticalSpeed;
}
