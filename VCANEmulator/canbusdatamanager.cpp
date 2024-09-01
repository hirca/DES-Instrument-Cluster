#include "canbusdatamanager.h"
#include <QDebug>
#include <QCanBus>

CANBusDataManager::CANBusDataManager(QObject *parent)
    : QObject(parent),
    m_speedCANId("0CFF6F7"),
    m_rpmCANId("0CFF6E7"),
    m_gearCANId("0CFE6C00"),
    m_batteryCANId("1801D0F3"),
    m_minSpeed(0),
    m_maxSpeed(140),
    m_speedIncreasing(true),
    m_speedStepSize(1),
    m_currentSpeed(0),
    m_minRPM(0),
    m_maxRPM(1000),
    m_rpmIncreasing(true),
    m_rpmStepSize(10),
    m_currentRPM(0),
    m_currentGear("P"),
    m_batteryLevel(50),
    m_isRunning(false),
    m_canDevice(nullptr),
    m_speedUpdateInterval(100),
    m_rpmUpdateInterval(100)
{
    connect(&m_speedTimer, &QTimer::timeout, this, &CANBusDataManager::updateSpeed);
    connect(&m_rpmTimer, &QTimer::timeout, this, &CANBusDataManager::updateRPM);

    m_speedTimer.setInterval(m_speedUpdateInterval);
    m_rpmTimer.setInterval(m_rpmUpdateInterval);

    if (connectToCANBus()) {
        sendInitialValues();
    } else {
        qDebug() << "Failed to connect to CAN bus";
    }
}


CANBusDataManager::~CANBusDataManager()
{
    if (m_canDevice) {
        m_canDevice->disconnectDevice();
        delete m_canDevice;
    }
}

bool CANBusDataManager::connectToCANBus()
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

QString CANBusDataManager::speedCANId() const
{
    return m_speedCANId;
}

void CANBusDataManager::setSpeedCANId(const QString &id)
{
    if (m_speedCANId != id) {
        m_speedCANId = id;
        emit speedCANIdChanged();
    }
}

QString CANBusDataManager::rpmCANId() const
{
    return m_rpmCANId;
}

void CANBusDataManager::setRpmCANId(const QString &id)
{
    if (m_rpmCANId != id) {
        m_rpmCANId = id;
        emit rpmCANIdChanged();
    }
}

QString CANBusDataManager::gearCANId() const
{
    return m_gearCANId;
}

void CANBusDataManager::setGearCANId(const QString &id)
{
    if (m_gearCANId != id) {
        m_gearCANId = id;
        emit gearCANIdChanged();
    }
}

QString CANBusDataManager::batteryCANId() const
{
    return m_batteryCANId;
}

void CANBusDataManager::setBatteryCANId(const QString &id)
{
    if (m_batteryCANId != id) {
        m_batteryCANId = id;
        emit batteryCANIdChanged();
    }
}

bool CANBusDataManager::isRunning() const
{
    return m_isRunning;
}

void CANBusDataManager::setSpeedRange(int min, int max)
{
    m_minSpeed = min;
    m_maxSpeed = max;
    m_currentSpeed = m_speedIncreasing ? min : max;
}

void CANBusDataManager::setSpeedProfile(bool increasing)
{
    m_speedIncreasing = increasing;
    m_currentSpeed = increasing ? m_minSpeed : m_maxSpeed;
}

void CANBusDataManager::setSpeedStepSize(int step)
{
    m_speedStepSize = step;
}

void CANBusDataManager::setRPMRange(int min, int max)
{
    m_minRPM = min;
    m_maxRPM = max;
    m_currentRPM = m_rpmIncreasing ? min : max;
}

void CANBusDataManager::setRPMProfile(bool increasing)
{
    m_rpmIncreasing = increasing;
    m_currentRPM = increasing ? m_minRPM : m_maxRPM;
}

void CANBusDataManager::setRPMStepSize(int step)
{
    m_rpmStepSize = step;
}

void CANBusDataManager::setGear(const QString &gear)
{
    if (m_currentGear != gear) {
        m_currentGear = gear;
        QByteArray data(8, 0);
        if (gear == "P") data[0] = 0x01;
        else if (gear == "N") data[0] = 0x02;
        else if (gear == "R") data[0] = 0x03;
        else if (gear == "D") data[0] = 0x04;
        sendCANMessage(m_gearCANId, data);
    }
}

void CANBusDataManager::setBatteryLevel(int level)
{
    if (m_batteryLevel != level) {
        m_batteryLevel = qBound(0, level, 100);
        QByteArray data(8, 0);
        data[0] = static_cast<char>(m_batteryLevel);
        sendCANMessage(m_batteryCANId, data);
        qDebug() << "Sent battery level:" << m_batteryLevel << "CAN ID:" << m_batteryCANId;
    }
}

void CANBusDataManager::start()
{
    if (!m_isRunning) {
        if (!m_canDevice || m_canDevice->state() != QCanBusDevice::ConnectedState) {
            if (!connectToCANBus()) {
                qDebug() << "Failed to connect to CAN bus. Cannot start.";
                return;
            }
        }
        sendInitialValues();  // Send initial values when starting
        m_speedTimer.start();
        m_rpmTimer.start();
        m_isRunning = true;
        emit isRunningChanged();
    }
}

void CANBusDataManager::stop()
{
    if (m_isRunning) {
        m_speedTimer.stop();
        m_rpmTimer.stop();
        m_isRunning = false;
        emit isRunningChanged();
    }
}

void CANBusDataManager::sendCANMessage(const QString &id, const QByteArray &data)
{
    if (!m_canDevice || m_canDevice->state() != QCanBusDevice::ConnectedState) {
        qDebug() << "CAN device not connected";
        return;
    }

    QCanBusFrame frame;
    frame.setFrameId(id.toUInt(nullptr, 16));
    frame.setPayload(data);

    if (!m_canDevice->writeFrame(frame)) {
        qDebug() << "Error sending CAN frame:" << m_canDevice->errorString();
    } else {
        qDebug() << "Sent CAN message:" << Qt::hex << id << data.toHex();
    }
}

void CANBusDataManager::updateSpeed()
{
    if (m_speedIncreasing) {
        m_currentSpeed += m_speedStepSize;
        if (m_currentSpeed > m_maxSpeed) m_currentSpeed = m_minSpeed;
    } else {
        m_currentSpeed -= m_speedStepSize;
        if (m_currentSpeed < m_minSpeed) m_currentSpeed = m_maxSpeed;
    }

    QByteArray data(8, 0);
    qint16 speed = static_cast<qint16>(m_currentSpeed);
    data[2] = static_cast<char>((speed >> 8) & 0xFF);
    data[3] = static_cast<char>(speed & 0xFF);
    sendCANMessage(m_speedCANId, data);
}

void CANBusDataManager::updateRPM()
{
    if (m_rpmIncreasing) {
        m_currentRPM += m_rpmStepSize;
        if (m_currentRPM > m_maxRPM) m_currentRPM = m_minRPM;
    } else {
        m_currentRPM -= m_rpmStepSize;
        if (m_currentRPM < m_minRPM) m_currentRPM = m_maxRPM;
    }

    QByteArray data(8, 0);
    qint16 rpm = static_cast<qint16>(m_currentRPM);
    data[4] = static_cast<char>((rpm >> 8) & 0xFF);
    data[5] = static_cast<char>(rpm & 0xFF);
    sendCANMessage(m_rpmCANId, data);
}

void CANBusDataManager::sendInitialValues()
{
    // Send initial battery level
    QByteArray batteryData(8, 0);
    batteryData[0] = static_cast<char>(m_batteryLevel);
    sendCANMessage(m_batteryCANId, batteryData);
    qDebug() << "Sent initial battery level:" << m_batteryLevel;

    // Send initial gear
    QByteArray gearData(8, 0);
    if (m_currentGear == "P") gearData[0] = 0x01;
    else if (m_currentGear == "N") gearData[0] = 0x02;
    else if (m_currentGear == "R") gearData[0] = 0x03;
    else if (m_currentGear == "D") gearData[0] = 0x04;
    sendCANMessage(m_gearCANId, gearData);
    qDebug() << "Sent initial gear:" << m_currentGear;

    // Send initial speed (0)
    QByteArray speedData(8, 0);
    sendCANMessage(m_speedCANId, speedData);
    qDebug() << "Sent initial speed: 0";

    // Send initial RPM (0)
    QByteArray rpmData(8, 0);
    sendCANMessage(m_rpmCANId, rpmData);
    qDebug() << "Sent initial RPM: 0";
}


int CANBusDataManager::speedUpdateInterval() const
{
    return m_speedUpdateInterval;
}

void CANBusDataManager::setSpeedUpdateInterval(int interval)
{
    if (m_speedUpdateInterval != interval) {
        m_speedUpdateInterval = interval;
        m_speedTimer.setInterval(interval);
        emit speedUpdateIntervalChanged();
    }
}

int CANBusDataManager::rpmUpdateInterval() const
{
    return m_rpmUpdateInterval;
}

void CANBusDataManager::setRpmUpdateInterval(int interval)
{
    if (m_rpmUpdateInterval != interval) {
        m_rpmUpdateInterval = interval;
        m_rpmTimer.setInterval(interval);
        emit rpmUpdateIntervalChanged();
    }
}
