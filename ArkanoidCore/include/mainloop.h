//
// Created by maxim on 17.07.2020.
//

#ifndef ARKANOID_MAINLOOP_H
#define ARKANOID_MAINLOOP_H
#include <iostream>
#include <memory>
#include <list>
#include "GemulingEngine/include/Window.h"
#include "Ball.h"
#include "Platform.h"
#include "Block.h"

int mainloop(std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks,
             std::unique_ptr<Window> &window, bool &isSpaceActive);

#endif //ARKANOID_MAINLOOP_H
