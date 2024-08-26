#include <QCanBus>
#include <QDebug>
#include <QTimer>

#include "idashboardbridge.h"


IDashboardBridge::IDashboardBridge(QObject *parent)
    : QObject(parent), m_canDevice(nullptr), m_speed(0), m_rpm(0), m_gear("P"), m_batteryLevel(0)
{
    // Use a single-shot timer to initialize the CAN bus connection
    // This ensures that the event loop is running before we attempt to connect
    QTimer::singleShot(0, this, &IDashboardBridge::initialize);
}

IDashboardBridge::~IDashboardBridge()
{
    if (m_canDevice) {
        m_canDevice->disconnectDevice();
        delete m_canDevice;
    }
}

void IDashboardBridge::initialize()
{
    if (connectToCANBus()) {
        connect(m_canDevice, &QCanBusDevice::framesReceived, this, [this]() {
            while (m_canDevice->framesAvailable()) {
                processCANFrame(m_canDevice->readFrame());
            }
        });
        qDebug() << "IDashboardBridge initialized and ready to receive frames";
    } else {
        qDebug() << "Failed to initialize IDashboardBridge";
    }
}

bool IDashboardBridge::connectToCANBus()
{
    if (QCanBus::instance()->plugins().contains("socketcan")) {
        m_canDevice = QCanBus::instance()->createDevice("socketcan", "vcan0");
        if (!m_canDevice) {
            qDebug() << "Error creating CAN device";
            return false;
        }

        if (!m_canDevice->connectDevice()) {
            qDebug() << "Error connecting to CAN device:" << m_canDevice->errorString();
            delete m_canDevice;
            m_canDevice = nullptr;
            return false;
        }

        return true;
    } else {
        qDebug() << "SocketCAN plugin not found";
        return false;
    }
}

void IDashboardBridge::processCANFrame(const QCanBusFrame &frame)
{
    switch (frame.frameId()) {
    case SPEED_FRAME_ID:
        processSpeedFrame(frame);
        break;
    case RPM_FRAME_ID:
        processRPMFrame(frame);
        break;
    case GEAR_FRAME_ID:
        processGearFrame(frame);
        break;
    case BATTERY_FRAME_ID:
        processBatteryFrame(frame);
        break;
    default:
        // Ignore other frames
        qDebug() << "Received unhandled frame with ID:" << Qt::hex << frame.frameId();
        break;
    }
}

void IDashboardBridge::processSpeedFrame(const QCanBusFrame &frame)
{
    if (frame.payload().size() >= 4) {
        int newSpeed = (frame.payload()[2] << 8) | frame.payload()[3];
        if (m_speed != newSpeed) {
            m_speed = newSpeed;
            emit speedChanged();
            qDebug() << "Speed updated:" << m_speed;
        }
    }
}

void IDashboardBridge::processRPMFrame(const QCanBusFrame &frame)
{
    if (frame.payload().size() >= 6) {
        int newRPM = (frame.payload()[4] << 8) | frame.payload()[5];
        if (m_rpm != newRPM) {
            m_rpm = newRPM;
            emit rpmChanged();
            qDebug() << "RPM updated:" << m_rpm;
        }
    }
}

void IDashboardBridge::processGearFrame(const QCanBusFrame &frame)
{
    if (frame.payload().size() >= 1) {
        QString newGear;
        switch (frame.payload()[0]) {
        case 0x01: newGear = "P"; break;
        case 0x02: newGear = "N"; break;
        case 0x03: newGear = "R"; break;
        case 0x04: newGear = "D"; break;
        default: newGear = "N"; break;
        }
        if (m_gear != newGear) {
            m_gear = newGear;
            emit gearChanged();
            qDebug() << "Gear updated:" << m_gear;
        }
    }
}

void IDashboardBridge::processBatteryFrame(const QCanBusFrame &frame)
{
    if (frame.payload().size() >= 1) {
        int newBatteryLevel = static_cast<unsigned char>(frame.payload()[0]);
        if (m_batteryLevel != newBatteryLevel) {
            m_batteryLevel = newBatteryLevel;
            emit batteryLevelChanged();
            qDebug() << "Battery level updated:" << m_batteryLevel;
        }
    }
}
