//
// Created by maxim on 16.07.2020.
//

#include "../include/Platform.h"


Platform::Platform(std::unique_ptr<Render> &&renderModel, short * platformMotion)
        : BaseGameObject(std::move(renderModel)), m_platformMotion(platformMotion)
{
    auto matValue = this->m_renderModel->getValue();
    setPosition(matValue);
}

void Platform::move(const float a)
{
    const float ot = 0.0001f;
    MatrixValue matVal = m_renderModel->getValue();

    if ((std::abs(1.f - this->m_model[0][0] + this->m_model[3][0]) > ot && a < 0)
    ||   std::abs(this->m_model[0][0] + this->m_model[3][0] - 1.f) > ot && a > 0) {
        matVal.a += a;
    }

    setPosition(matVal);
}
