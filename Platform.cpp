//
// Created by maxim on 03.07.2019.
//

#include "Platform.h"

Platform::Platform(ObjectCreater object, GLFWwindow *mainwindow, Shader shader, bool *motionSetting)
    : BaseGameObject(object, mainwindow,shader),motionSet(motionSetting),lenBoolArr(2){}


void Platform::update()
{
    static const float lim = 0.7f;
    if(motionSet[0] && a > -lim)
    {
        a+=-0.1f;
        motionSet[0]=false;
    }

    if(motionSet[1] && a < lim)
    {
        a+=0.1f;
        motionSet[1]=false;
    }
}

