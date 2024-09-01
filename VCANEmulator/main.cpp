#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "canbusdatamanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CANBusDataManager canBusDataManager;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("canBusDataManager", &canBusDataManager);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("VCANEmulator", "Main");

    return app.exec();
}
