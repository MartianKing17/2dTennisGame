//
// Created by maxim on 22.05.2019.
//

//#include "GameEngine/filedata.h"
#include "Game.h"
#include <QGuiApplication>
#include <QtQml/QQmlContext>
#include <QScreen>
#include <QUrl>
#include <QIcon>
#include <QString>
#include <QtQml/QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    QString ico_file_name = "arkanoid-ico.ico";
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(ico_file_name));
    qmlRegisterType<Game>("gameFunc",1,0,"Game");
    Game game;
    game.setScreenSize(app.primaryScreen()->geometry());
    QQmlApplicationEngine engine;
    QQmlContext * cntx = engine.rootContext();
    cntx->setContextProperty("gameEvent", &game);
    const QUrl url(QStringLiteral("main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
