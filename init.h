//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_INIT_H
#define ARKANOID_INIT_H
#include "GameEngine/graphics.h"
#include <vector>
#include <chrono>
#include <list>
#include <memory>
#include <thread>
#include "Ball.h"
#include "Platform.h"
#include "Block.h"

void makeBlock(GLFWwindow * window, MatrixValue matrixValue, std::string picturePath, std::list<std::shared_ptr<Block>> &blocks);

std::list<Block> createBlocks(GLFWwindow *window);

std::unique_ptr<Ball> makeBall(GLFWwindow *window);

std::unique_ptr<Platform> makePlatform(GLFWwindow *window, short *platformMotion);

int mainloop(std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks, GLFWwindow *window, bool &isSpaceActive);

#endif //ARKANOID_INIT_H
