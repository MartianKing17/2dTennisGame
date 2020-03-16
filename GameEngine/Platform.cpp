//
// Created by maxim on 03.07.2019.
//

#include "Platform.h"

Platform::Platform(ObjectCreater object, GLFWwindow *mainwindow, Shader shader, bool *motionSetting)
    : BaseGameObject(object, mainwindow,shader),motionSet(motionSetting),lenBoolArr(2)
    {
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
    glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);

    glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    glm::mat4 model=glm::mat4(1.f);
    model=glm::translate(model, glm::vec3(a, b, c));
    model=glm::scale(model, glm::vec3(sx, sy, sz));

    this->worldModel = projection * camera * model;

    cx = worldModel[0][0] * (float)objProjCoor.first + worldModel[3][0] ;
    cy = worldModel[1][1]  * (float)objProjCoor.second + worldModel[3][1];

    static const float lim = 0.7f;
    if(motionSet[0] && a > -lim)
    {
        a+=-0.025f;
    }

    if(motionSet[1] && a < lim)
    {
        a+=0.025f;
    }
}
