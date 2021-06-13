//
// Created by maxim on 22.05.2019.
//

#include "QGame.h"
#include <QGuiApplication>
#include <QApplication>
#include <QtQml/QQmlContext>
#include <QScreen>
#include <QUrl>
#include <QIcon>
#include <QString>
#include <QtQml/QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QString ico_file_name = "picture/arkanoid-ico.ico";
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(ico_file_name));
    qmlRegisterType<QGame>("Game", 1, 0, "Game");
    QQmlApplicationEngine engine;
    const QUrl url("qrc:/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
