//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_PLATFORM_H
#define ARKANOID_PLATFORM_H

#include <utility>
#include "BaseGameObject.h"

class Platform:public BaseGameObject
{
    short * platformMotion;
    float left, right, top, bottom;
public:
    Platform()=default;
    Platform(GLFWwindow *mainwindow, RenderModel *renderModel, short *platfromMotion);
    void update() override;
    float getLeft();
    float getRight();
    float getTop();
    float getBottom();
};

#endif //ARKANOID_PLATFORM_H
