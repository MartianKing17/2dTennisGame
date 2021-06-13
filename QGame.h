//
// Created by maxim on 29.01.21.
//

#ifndef ARKANOID_QGAME_H
#define ARKANOID_QGAME_H

#include <QObject>
#include <QMessageBox>
#include <memory>
#include "ArkanoidCore/include/Game.h"

class QGame : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned int level WRITE setLevel)
    Q_PROPERTY(QString windowMode WRITE setMode)
public:
    QGame(QObject * parent = nullptr);
    Q_INVOKABLE bool startSinglePlay();
    Q_INVOKABLE unsigned int getLevel()
    {
        return m_game->getMaxLevel();
    }

    Q_INVOKABLE QString getWindowMode()
    {
        return QString::fromStdString(m_game->getWindowMode());
    }

    Q_INVOKABLE void writeData()
    {
        try {
            m_game->writeData();
        }  catch (const std::runtime_error& e) {
            QMessageBox::critical(nullptr, "Error", e.what());
        }
    }

    void setLevel(unsigned int gameLevel)
    {
        m_level = gameLevel;
        m_game->setLevel(m_level);
    }

    void setMode(QString windowMode)
    {
        m_windowMode = windowMode;
        m_game->setWindowMode(m_windowMode.toStdString());
    }

    ~QGame() = default;
signals:
    void maxLevelChanged(int maxLevel);
private:
    std::unique_ptr<Game> m_game;
    bool m_isGood;
    unsigned int m_level;
    QString m_windowMode;
};


#endif //ARKANOID_QGAME_H
