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
    Platform(std::unique_ptr<Render> &&renderModel, short * platformMotion);
    void move(const float a);
private:
    short * m_platformMotion;
};

#endif //ARKANOID_PLATFORM_H
