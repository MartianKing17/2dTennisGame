//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H
#include "BaseGameObject.h"
#include <utility>
#include <functional>

class Ball:public BaseGameObject
{
    std::function<bool()> handler;
    float verticalSpeed, gorizontalSpeed;
public:
    Ball(GLFWwindow *mainwindow, RenderModel *renderModel, std::function<bool()> handler);
    void update() override;
    void setSpeed(float gorizontalSpeed, float verticalSpeed);
};

#endif //ARKANOID_BALL_H
