//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_GAME_H
#define ARKANOID_GAME_H

#include <QGuiApplication>
#include <QDesktopWidget>
#include <QObject>
#include <QRect>

class Game: public QObject
{
    Q_OBJECT

public:
    Game(QObject * parent = nullptr);
    void setScreenSize(QRect screenSize);
    Q_INVOKABLE bool startSinglePlay();
    Q_INVOKABLE bool startMuiliPlay();
    Q_INVOKABLE void achievementPage();
    Q_INVOKABLE void settingMenu();
    Q_INVOKABLE int getWidth();
    Q_INVOKABLE int getHeight();
    ~Game();

private:
    QRect screen;
};


#endif //ARKANOID_GAME_H
