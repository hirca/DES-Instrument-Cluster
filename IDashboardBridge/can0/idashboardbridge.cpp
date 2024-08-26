#include <QCanBus>
#include <QTimer>
#include <QDebug>
#include "idashboardbridge.h"


IDashboardBridge::IDashboardBridge(QObject *parent)
    : QObject(parent), m_canDevice(nullptr), m_speed(0), m_rpm(0), m_gear("P"), m_batteryLevel(0)
{
    QTimer::singleShot(0, this, &IDashboardBridge::initialize);
}

IDashboardBridge::~IDashboardBridge()
{
    if (m_canDevice) {
        m_canDevice->disconnectDevice();
        delete m_canDevice;
    }
}

int IDashboardBridge::speed() const
{
    return m_speed;
}

int IDashboardBridge::rpm() const
{
    return m_rpm;
}

QString IDashboardBridge::gear() const
{
    return m_gear;
}

int IDashboardBridge::batteryLevel() const
{
    return m_batteryLevel;
}

void IDashboardBridge::initialize()
{
    if (connectToCANBus()) {
        connect(m_canDevice, &QCanBusDevice::framesReceived, this, &IDashboardBridge::processReceivedFrames);
        qDebug() << "IDashboardBridge initialized and ready to receive frames";
    } else {
        qDebug() << "Failed to initialize IDashboardBridge";
    }
}

bool IDashboardBridge::connectToCANBus()
{
    if (QCanBus::instance()->plugins().contains("socketcan")) {
        m_canDevice = QCanBus::instance()->createDevice("socketcan", "can0");
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

void IDashboardBridge::processReceivedFrames()
{
    while (m_canDevice && m_canDevice->framesAvailable()) {
        processCANFrame(m_canDevice->readFrame());
    }
}

void IDashboardBridge::processCANFrame(const QCanBusFrame &frame)
{
    if (frame.frameId() == CAN_FRAME_ID && frame.payload().size() >= 4) {
        int newRPM = (frame.payload()[0] << 8) | frame.payload()[1];
        float newSpeed = ((frame.payload()[2] << 8) | frame.payload()[3]) / 100.0;

        if (m_rpm != newRPM) {
            m_rpm = newRPM;
            emit rpmChanged();
            qDebug() << "RPM updated:" << m_rpm;
        }

        if (m_speed != static_cast<int>(newSpeed)) {
            m_speed = static_cast<int>(newSpeed);
            emit speedChanged();
            qDebug() << "Speed updated:" << m_speed;
        }

        // Placeholder updates for gear and battery level
        // You can modify or remove these as needed
        if (m_gear != "D") {
            m_gear = "D";
            emit gearChanged();
        }
        if (m_batteryLevel != 75) {
            m_batteryLevel = 75;
            emit batteryLevelChanged();
        }
    } else {
        qDebug() << "Received unhandled frame with ID:" << Qt::hex << frame.frameId();
    }
}