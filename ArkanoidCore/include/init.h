//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_INIT_H
#define ARKANOID_INIT_H

#include <vector>
#include <chrono>
#include <list>
#include <memory>
#include <thread>
#include "GemulingEngine/include/Window.h"
#include "Ball.h"
#include "Platform.h"
#include "Block.h"

void makeBlock(const std::string& lvlFilename, std::list<std::shared_ptr<Block>> &blocks);
std::unique_ptr<Ball> makeBall();
std::unique_ptr<Platform> makePlatform(short *platformMotion);

#endif //ARKANOID_INIT_H
