#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>
#include <QFont>
#include "idashboardbridge.h"



int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/assets/font/Bebas-Regular.ttf");
    app.setFont(QFont("Bebas"));


    QQmlApplicationEngine engine;
    IDashboardBridge idashboardBridge;
    engine.rootContext()->setContextProperty("idashboardBridge", &idashboardBridge);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Dashboard", "Dashboard");

    return app.exec();
}
