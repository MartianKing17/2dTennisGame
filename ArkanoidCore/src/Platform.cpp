//
// Created by maxim on 16.07.2020.
//

#include "../include/Platform.h"

Platform::Platform(Render * renderModel, short * platformMotion)
        : BaseGameObject(renderModel), m_platformMotion(platformMotion),
          m_left(0.), m_right(0.), m_bottom(0.), m_top(0.)
{
    auto matValue = this->renderModel->getValue();
    setPosition(matValue);
    this->m_left = this->m_right = this->radius / 5;
    this->m_top = this->m_bottom = this->radius / 5;
}

float Platform::getTop()
{
    return getVerticalPlace() + this->m_top;
}

float Platform::getBottom()
{
    return getVerticalPlace() - this->m_bottom;
}

float Platform::getLeft()
{
    return getGorizontalPlace() - this->radius + m_left;
}

float Platform::getRight()
{
    return getGorizontalPlace() + this->radius - m_right;
}

void Platform::update()
{
    const float ot = 0.0001f;
    MatrixValue matVal = renderModel->getValue();

    if (((*m_platformMotion == -1) && std::abs(1.f - this->model[0][0] + this->model[3][0]) > ot)) {
        matVal.a += -0.02f;
    }

    if (((*m_platformMotion == 1) && std::abs(this->model[0][0] + this->model[3][0] - 1.f) > ot)) {
        matVal.a += 0.02f;
    }

    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matVal.a, matVal.b, matVal.c));
    this->model = glm::scale(this->model, glm::vec3(matVal.sx, matVal.sy, matVal.sz));
    renderModel->setValue(matVal);
}
