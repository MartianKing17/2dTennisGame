//
// Created by maxim on 22.05.2019.
//

//#include "GemulingEngine/filedata.h"
#include "QGame.h"
#include <QGuiApplication>
#include <QApplication>
#include <QtQml/QQmlContext>
#include <QScreen>
#include <QUrl>
#include <QIcon>
#include <QString>
#include <QtQml/QQmlApplicationEngine>

/*
 TODO:
     * make the better physics
*/

int main(int argc, char *argv[])
{
    QString ico_file_name = "arkanoid-ico.ico";
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(ico_file_name));
    qmlRegisterType<QGame>("Game",1,0,"Game");
    QGame game;
    QQmlApplicationEngine engine;
    QQmlContext * cntx = engine.rootContext();
    cntx->setContextProperty("gameEvent", &game);
    const QUrl url("qrc:/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
