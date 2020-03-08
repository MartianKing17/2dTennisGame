//
// Created by maxim on 03.07.2019.
//

#ifndef INC_2DTENNISGAME_BALL_H
#define INC_2DTENNISGAME_BALL_H

#include "BaseGameObject.h"
#include <utility>

class Ball:public BaseGameObject
{
    bool ball_forward;
    void func();
    int verticalSpeed, gorizontalSpeed;
public:
    Ball(ObjectCreater object, GLFWwindow *mainwindow, Shader shader, bool &ball_forward);
    void update() override;
    void setSpeed();
    void calcBallForwarding();
};


#endif //INC_2DTENNISGAME_BALL_H
