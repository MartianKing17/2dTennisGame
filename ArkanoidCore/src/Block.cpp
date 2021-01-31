//
// Created by maxim on 16.07.2020.
//

#include "../include/Block.h"

Block::Block(Render *renderModel)
        : BaseGameObject(renderModel)
{
    auto matValue = this->renderModel->getValue();
    setPosition(matValue);
}

void Block::update()
{
    MatrixValue matVal = renderModel->getValue();
    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matVal.a, matVal.b, matVal.c));
    this->model = glm::scale(this->model, glm::vec3(matVal.sx, matVal.sy, matVal.sz));
}
