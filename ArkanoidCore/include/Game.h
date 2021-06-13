//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_GAME_H
#define ARKANOID_GAME_H

#include <vector>
#include <string>
#include <list>
#include <memory>
#include "Ball.h"
#include "Platform.h"
#include "Block.h"
#include "../GemulingEngine/include/Window.h"

class Game
{
public:
    Game();
    unsigned int startSinglePlay();
    void setLevel(unsigned int level);
    void setWindowMode(std::string mode);
    std::string getWindowMode();
    unsigned int getMaxLevel();
    void writeData();
    ~Game() = default;
private:
    std::string m_windowMode;
    unsigned int m_level;
    unsigned int m_maxLevel;
    std::shared_ptr<Ball> m_ball;
    std::shared_ptr<Platform> m_platform;
    std::list<std::shared_ptr<Block>> m_blocks;
    void getClearDataFromFile();
};


#endif //ARKANOID_GAME_H
