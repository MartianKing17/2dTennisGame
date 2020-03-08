//
// Created by maxim on 03.07.2019.
//

#include "Ball.h"

Ball::Ball(ObjectCreater object, GLFWwindow *mainwindow, Shader shader, bool &ball_forward)
    : BaseGameObject(object, mainwindow,shader)
    ,verticalSpeed(0),gorizontalSpeed(0),ball_forward(ball_forward){}


void Ball::func()
{
    return;
}

void Ball::calcBallForwarding()
{

    return;
}

void Ball::update()
{

    if(!ball_forward)
    {
        b += -0.025f;
    }
    else
    {
        b += 0.025f;
    }
}

void Ball::setSpeed()
{
    return;
}

