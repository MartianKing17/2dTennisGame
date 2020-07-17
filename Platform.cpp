//
// Created by maxim on 16.07.2020.
//

#include "Platform.h"

Platform::Platform(GLFWwindow *mainwindow, RenderModel *renderModel, short *platfromMotion)
        : BaseGameObject(mainwindow, renderModel), platformMotion(platfromMotion)
{
    auto matValue = this->renderModel->getValues();
    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matValue.a, matValue.b, matValue.c));
    this->model = glm::scale(this->model, glm::vec3(matValue.sx, matValue.sy, matValue.sz));
    this->left = this->right = this->radius / 5;
    this->top = this->bottom = this->radius / 5;
}

float Platform::getTop()
{
    return getVerticalPlace() + this->top;
}

float Platform::getBottom()
{
    return getVerticalPlace() - this->bottom;
}

float Platform::getLeft()
{
    return getGorizontalPlace() - this->radius + left;
}

float Platform::getRight()
{
    return getGorizontalPlace() + this->radius - right;
}

void Platform::update()
{
    MatrixValue matVal = renderModel->getValues();

    const float lim = 0.738f;

    if ((*platformMotion == -1) && matVal.a > -lim) {
        matVal.a += -0.02f;
    }

    if ((*platformMotion == 1) && matVal.a < lim) {
        matVal.a += 0.02f;
    }

    this->model = glm::mat4(1.f);
    this->model = glm::translate(this->model, glm::vec3(matVal.a, matVal.b, matVal.c));
    this->model = glm::scale(this->model, glm::vec3(matVal.sx, matVal.sy, matVal.sz));

    renderModel->setValues(matVal);
}
