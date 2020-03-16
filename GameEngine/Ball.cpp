//
// Created by maxim on 03.07.2019.
//

#include "Ball.h"

Ball::Ball(ObjectCreater object, GLFWwindow *mainwindow, Shader shader)
    : BaseGameObject(object, mainwindow,shader),verticalSpeed(-0.01f),gorizontalSpeed(0){}

void Ball::update()
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

    a += gorizontalSpeed;
    b += verticalSpeed;
}

void Ball::setSpeed(float gorizontalSpeed, float verticalSpeed)
{
    this->gorizontalSpeed = gorizontalSpeed;
    this->verticalSpeed   = verticalSpeed;
}

