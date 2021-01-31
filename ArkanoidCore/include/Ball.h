//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H

#include <utility>
#include <functional>
#include "BaseGameObject.h"

class Ball : public BaseGameObject
{
public:
    Ball(Render *renderModel);
    void update() override;
    void setSpeed(float horizontalSpeed, float verticalSpeed);
private:
    float m_verticalSpeed;
    float m_horizontalSpeed;
};

#endif //ARKANOID_BALL_H
