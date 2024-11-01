#include "canreader.h"
#include <QCanBus>
#include <QCanBusFrame>
#include <QDebug>
#include <QVariant>
#include <cmath>

CANReader::CANReader(QObject *parent)
    : QObject(parent)
    , m_device(nullptr)
    , m_timer(nullptr)
    , m_rpm(0)
    , m_lastReceivedRPM(0)
    , m_speed(0.0)
    , m_gearState("N")
    , m_rpmReadings(FILTER_SIZE, 0)
    , m_rpmSum(0)
{
    setupCANDevice();

    // Set up timer for periodic updates
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CANReader::updateRPM);
    m_timer->start(100);  // Update every 100 ms
}

CANReader::~CANReader()
{
    if (m_device) {
        m_device->disconnectDevice();
        delete m_device;
    }
}

void CANReader::setupCANDevice()
{
    QString errorString;
    m_device = QCanBus::instance()->createDevice("socketcan", "can0", &errorString);
    if (!m_device) {
        qWarning() << "Error creating CAN device:" << errorString;
        return;
    }

    // Attempt to set the bitrate
    QVariant bitrate(500000); // 500 kbps
    m_device->setConfigurationParameter(QCanBusDevice::BitRateKey, bitrate);

    // Check if the bitrate was set correctly
    if (m_device->configurationParameter(QCanBusDevice::BitRateKey).toInt() != 500000) {
        qWarning() << "Failed to set bitrate. Current bitrate:"
                   << m_device->configurationParameter(QCanBusDevice::BitRateKey).toInt();
        qWarning() << "Continuing with current bitrate. This may cause communication issues if it doesn't match your CAN network.";
    }

    if (!m_device->connectDevice()) {
        qWarning() << "Error connecting to CAN device:" << m_device->errorString();
        delete m_device;
        m_device = nullptr;
        return;
    }

    connect(m_device, &QCanBusDevice::framesReceived, this, &CANReader::processReceivedFrames);
    qDebug() << "CAN device connected successfully";

    // Print current configuration
    qDebug() << "CAN Configuration:";
    qDebug() << "  Bitrate:" << m_device->configurationParameter(QCanBusDevice::BitRateKey).toInt() << "bps";
    qDebug() << "  Raw Filter:" << m_device->configurationParameter(QCanBusDevice::RawFilterKey).toBool();
    qDebug() << "  Error Filter:" << m_device->configurationParameter(QCanBusDevice::ErrorFilterKey).toInt();
    qDebug() << "  Loopback:" << m_device->configurationParameter(QCanBusDevice::LoopbackKey).toBool();
    qDebug() << "  Receive Own:" << m_device->configurationParameter(QCanBusDevice::ReceiveOwnKey).toBool();
}

int CANReader::rpm() const
{
    return m_rpm;
}

double CANReader::speed() const
{
    return m_speed;
}

QString CANReader::gearState() const
{
    return m_gearState;
}

void CANReader::processReceivedFrames()
{
    if (!m_device) {
        qWarning() << "CAN device not initialized";
        return;
    }

    while (m_device->framesAvailable()) {
        const QCanBusFrame frame = m_device->readFrame();

        if (frame.frameId() == 0x100) {  // Check if it's the RPM message
            QByteArray payload = frame.payload();
            if (payload.size() >= 4) {
                float rpm;
                memcpy(&rpm, payload.constData(), sizeof(float));
                m_lastReceivedRPM = static_cast<int>(rpm);
                addRPMReading(m_lastReceivedRPM);
                qDebug() << "Received RPM:" << m_lastReceivedRPM;
            }
        }
    }
}

void CANReader::updateRPM()
{
    int newRPM = calculateAverageRPM();
    if (m_rpm != newRPM) {
        m_rpm = newRPM;
        emit rpmChanged();
        calculateSpeed();
        updateGearState();
    }
}

void CANReader::addRPMReading(int rpm)
{
    m_rpmSum -= m_rpmReadings[0];
    for (int i = 0; i < FILTER_SIZE - 1; ++i) {
        m_rpmReadings[i] = m_rpmReadings[i + 1];
    }
    m_rpmReadings[FILTER_SIZE - 1] = rpm;
    m_rpmSum += rpm;
}

int CANReader::calculateAverageRPM() const
{
    return m_rpmSum / FILTER_SIZE;
}

void CANReader::calculateSpeed()
{
    // Calculate speed in km/h
    // Speed (km/h) = (RPM / Gear Ratio) * Wheel Circumference * 60 / 1000
    double newSpeed = (m_rpm / GEAR_RATIO) * WHEEL_CIRCUMFERENCE * 60.0 / 1000.0;

    if (std::abs(m_speed - newSpeed) > 0.1) {  // Only update if change is significant
        m_speed = newSpeed;
        emit speedChanged();
    }
}

void CANReader::updateGearState()
{
    QString newGearState = (m_rpm > 0) ? "D" : "N";
    if (m_gearState != newGearState) {
        m_gearState = newGearState;
        emit gearStateChanged();
    }
}
