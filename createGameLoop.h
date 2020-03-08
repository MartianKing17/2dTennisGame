//
// Created by maxim on 05.08.2019.
//

#ifndef INC_2DTENNISGAME_CREATEGAMELOOP_H
#define INC_2DTENNISGAME_CREATEGAMELOOP_H

#include "include/graphics.h"
#include <vector>
#include "Ball.h"
#include "Platform.h"
#include "ObjectCreater.h"

BaseGameObject *createBall(GLFWwindow *window);

BaseGameObject *createPlatform(GLFWwindow *window, bool *motionSet);

void mainloop(BaseGameObject *ball, BaseGameObject *platform, GLFWwindow *window, bool &isSpaceActive);

#endif //INC_2DTENNISGAME_CREATEGAMELOOP_H
