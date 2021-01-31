//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_PLATFORM_H
#define ARKANOID_PLATFORM_H

#include <utility>
#include "BaseGameObject.h"

class Platform : public BaseGameObject
{
public:
    Platform(Render * renderModel, short * platformMotion);
    void update() override;
    float getLeft();
    float getRight();
    float getTop();
    float getBottom();
private:
    short * m_platformMotion;
    float m_left, m_right, m_top, m_bottom;
};

#endif //ARKANOID_PLATFORM_H
