//
// Created by maxim on 29.01.21.
//

#include "QGame.h"
#include <QMessageBox>

QGame::QGame(QObject * parent) : QObject(parent), m_game(nullptr)
{
    m_game = new Game();
}
bool QGame::startSinglePlay()
{
    try {
        m_game->startSinglePlay();
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(nullptr, "Error", e.what());
        return false;
    } catch (...) {
        QMessageBox::critical(nullptr, "Error", "Huston we have a some problem");
        return false;
    }

    return true;
}

void QGame::settingMenu()
{
    m_game->settingMenu();
}

QGame::~QGame()
{
    delete m_game;
}