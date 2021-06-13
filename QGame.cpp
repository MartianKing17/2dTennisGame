//
// Created by maxim on 29.01.21.
//

#include "QGame.h"
#include <QMessageBox>
#include <fstream>

QGame::QGame(QObject * parent)
    : QObject(parent), m_game(nullptr), m_level(0), m_isGood(true), m_windowMode("")
{
    try {
        m_game = std::make_unique<Game>();
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(nullptr, "Error", e.what());
        m_isGood = false;
    }
}
bool QGame::startSinglePlay()
{
    bool res{};
    int result{};
    if (!m_isGood) {
        return m_isGood;
    }

    try {
        result = m_game->startSinglePlay();
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(nullptr, "Error", e.what());
        return false;
    } catch (...) {
        QMessageBox::critical(nullptr, "Error", "Huston we have a some problem");
        return false;
    }

    if (result == 2) {
        res = false;
        emit maxLevelChanged(getLevel());
    }

    return res;
}
