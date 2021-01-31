//
// Created by maxim on 29.01.21.
//

#ifndef ARKANOID_QGAME_H
#define ARKANOID_QGAME_H

#include <QObject>
#include "ArkanoidCore/include/Game.h"

class QGame : public QObject
{
    Q_OBJECT
public:
    QGame(QObject * parent = nullptr);
    Q_INVOKABLE bool startSinglePlay();
    Q_INVOKABLE void settingMenu();
    ~QGame();
private:
    Game * m_game;
};


#endif //ARKANOID_QGAME_H
