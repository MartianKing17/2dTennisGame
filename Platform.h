//
// Created by maxim on 03.07.2019.
//

#ifndef INC_2DTENNISGAME_PLATFORM_H
#define INC_2DTENNISGAME_PLATFORM_H

#include <utility>
#include "BaseGameObject.h"

class Platform:public BaseGameObject
{
    float left, right, top, bottom;
    const std::size_t lenBoolArr;
    bool *motionSet;
public:
    Platform()=default;
    Platform(ObjectCreater object, GLFWwindow *mainwindow, Shader shader, bool *motionSetting);
    void update() override;
    float getLeft();
    float getRight();
    float getTop();
    float getBottom();
};



#endif //INC_2DTENNISGAME_PLATFORM_H
