//
// Created by maxim on 03.07.2019.
//

#ifndef INC_2DTENNISGAME_BALL_H
#define INC_2DTENNISGAME_BALL_H

#include "BaseGameObject.h"
#include <utility>

class Ball:public BaseGameObject
{
    float verticalSpeed, gorizontalSpeed;
public:
    Ball(ObjectCreater object, GLFWwindow *mainwindow, Shader shader);
    void update() override;
    void setSpeed(float gorizontalSpeed, float verticalSpeed);
};


#endif //INC_2DTENNISGAME_BALL_H
