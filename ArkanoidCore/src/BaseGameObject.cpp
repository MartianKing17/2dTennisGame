//
// Created by maxim on 16.07.2020.
//

#include "../include/BaseGameObject.h"


BaseGameObject::BaseGameObject(std::unique_ptr<Render> &&renderModel)
        : m_renderModel(std::move(renderModel))
{}

void BaseGameObject::setPosition(MatrixValue matrixValue)
{
    m_model = glm::mat4(1.f);
    m_model = glm::translate(m_model, glm::vec3(matrixValue.a, matrixValue.b, matrixValue.c));
    m_model = glm::scale(m_model, glm::vec3(matrixValue.sx, matrixValue.sy, matrixValue.sz));
    m_renderModel->setValue(matrixValue);
}

glm::mat4 BaseGameObject::getPosition()
{
    return m_model;
}

void BaseGameObject::render()
{
    m_renderModel->render(m_model);
}
