//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_GAME_H
#define ARKANOID_GAME_H

#include <vector>
#include <string>

class Game
{
public:
    Game() = default;
    bool startSinglePlay();
    void settingMenu();
    ~Game();
private:
    unsigned int m_availableMaxLevel;
    static std::vector<std::string> getClearDataFromFile();
};


#endif //ARKANOID_GAME_H
