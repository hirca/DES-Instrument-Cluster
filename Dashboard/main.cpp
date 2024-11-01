#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>
#include <QFont>
#include "i2cina219.h"
#include "canreader.h"

int main(int argc, char *argv[])
{
    // Initialize the GUI application
    QGuiApplication app(argc, argv);

    // Set up custom font
    QFontDatabase::addApplicationFont(":/assets/font/Bebas-Regular.ttf");
    app.setFont(QFont("Bebas"));

    // Initialize QML engine and backend objects
    QQmlApplicationEngine engine;
    I2CIna219 battery;                 // Battery monitoring interface
    CANReader canReader;               // CAN bus interface

    // Register C++ objects with QML context
    engine.rootContext()->setContextProperty("canReader", &canReader);
    engine.rootContext()->setContextProperty("battery", &battery);

    // Handle QML engine errors
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );

    // Load the main QML module
    engine.loadFromModule("Dashboard", "Dashboard");

    // Start the event loop
    return app.exec();
}