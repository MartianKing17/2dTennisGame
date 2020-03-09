//
// Created by maxim on 05.08.2019.
//

#ifndef INC_2DTENNISGAME_CREATEGAMELOOP_H
#define INC_2DTENNISGAME_CREATEGAMELOOP_H

#include "include/graphics.h"
#include <vector>
#include <chrono>
#include <list>
#include <thread>
#include "Ball.h"
#include "Platform.h"
#include "Block.h"
#include "ObjectCreater.h"

std::list<Block> * createBlocks(GLFWwindow *window);

BaseGameObject *createBall(GLFWwindow *window);

BaseGameObject *createPlatform(GLFWwindow *window, bool *motionSet);

void mainloop(BaseGameObject *ball, BaseGameObject *platform, std::list<Block> *blocks, GLFWwindow *window, bool &isSpaceActive);

#endif //INC_2DTENNISGAME_CREATEGAMELOOP_H
