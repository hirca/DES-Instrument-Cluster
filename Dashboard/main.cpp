#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>
#include <QFont>
#include "i2cina219.h"
#include "canreader.h"


int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/assets/font/Bebas-Regular.ttf");
    app.setFont(QFont("Bebas"));


    QQmlApplicationEngine engine;
    I2CIna219 battery;
    CANReader canReader;
    engine.rootContext()->setContextProperty("canReader", &canReader);
    engine.rootContext()->setContextProperty("battery", &battery);
    // IDashboardBridge idashboardBridge;
    // engine.rootContext()->setContextProperty("idashboardBridge", &idashboardBridge);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Dashboard", "Dashboard");

    return app.exec();
}
