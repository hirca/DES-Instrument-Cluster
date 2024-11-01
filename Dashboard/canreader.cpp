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
    , m_rpmReadings(FILTER_SIZE, 0)  // Initialize vector with zeros
    , m_rpmSum(0)
{
    setupCANDevice();

    // Initialize periodic update timer
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
    
    // Create CAN device using socketcan driver
    m_device = QCanBus::instance()->createDevice("socketcan", "can0", &errorString);
    if (!m_device) {
        qWarning() << "Error creating CAN device:" << errorString;
        return;
    }

    // Configure CAN bus parameters
    QVariant bitrate(500000);  // Set bitrate to 500 kbps
    m_device->setConfigurationParameter(QCanBusDevice::BitRateKey, bitrate);

    // Verify bitrate configuration
    if (m_device->configurationParameter(QCanBusDevice::BitRateKey).toInt() != 500000) {
        qWarning() << "Failed to set bitrate. Current bitrate:"
                   << m_device->configurationParameter(QCanBusDevice::BitRateKey).toInt();
        qWarning() << "Continuing with current bitrate. This may cause communication issues.";
    }

    // Connect to CAN device
    if (!m_device->connectDevice()) {
        qWarning() << "Error connecting to CAN device:" << m_device->errorString();
        delete m_device;
        m_device = nullptr;
        return;
    }

    // Set up frame reception handler
    connect(m_device, &QCanBusDevice::framesReceived, this, &CANReader::processReceivedFrames);
    
    // Log successful connection and configuration
    logDeviceConfiguration();
}

void CANReader::processReceivedFrames()
{
    if (!m_device) {
        qWarning() << "CAN device not initialized";
        return;
    }

    // Process all available frames
    while (m_device->framesAvailable()) {
        const QCanBusFrame frame = m_device->readFrame();

        // Process RPM message (ID: 0x100)
        if (frame.frameId() == 0x100) {
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
    // Update RPM and dependent values if changed
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
    // Implement moving average filter
    m_rpmSum -= m_rpmReadings[0];
    
    // Shift values in circular buffer
    for (int i = 0; i < FILTER_SIZE - 1; ++i) {
        m_rpmReadings[i] = m_rpmReadings[i + 1];
    }
    
    // Add new reading
    m_rpmReadings[FILTER_SIZE - 1] = rpm;
    m_rpmSum += rpm;
}

int CANReader::calculateAverageRPM() const
{
    return m_rpmSum / FILTER_SIZE;
}

void CANReader::calculateSpeed()
{
    // Convert RPM to vehicle speed (km/h)
    // Formula: Speed = (RPM / Gear Ratio) * Wheel Circumference * (60 min/h) / (1000 m/km)
    double newSpeed = (m_rpm / GEAR_RATIO) * WHEEL_CIRCUMFERENCE * 60.0 / 1000.0;

    // Update speed if change is significant (>0.1 km/h)
    if (std::abs(m_speed - newSpeed) > 0.1) {
        m_speed = newSpeed;
        emit speedChanged();
    }
}

void CANReader::updateGearState()
{
    // Update gear state based on RPM
    QString newGearState = (m_rpm > 0) ? "D" : "N";
    if (m_gearState != newGearState) {
        m_gearState = newGearState;
        emit gearStateChanged();
    }
}

// Getter methods
int CANReader::rpm() const { return m_rpm; }
double CANReader::speed() const { return m_speed; }
QString CANReader::gearState() const { return m_gearState; }

// Private helper method for logging device configuration
void CANReader::logDeviceConfiguration() const
{
    qDebug() << "CAN device connected successfully";
    qDebug() << "CAN Configuration:";
    qDebug() << "  Bitrate:" << m_device->configurationParameter(QCanBusDevice::BitRateKey).toInt() << "bps";
    qDebug() << "  Raw Filter:" << m_device->configurationParameter(QCanBusDevice::RawFilterKey).toBool();
    qDebug() << "  Error Filter:" << m_device->configurationParameter(QCanBusDevice::ErrorFilterKey).toInt();
    qDebug() << "  Loopback:" << m_device->configurationParameter(QCanBusDevice::LoopbackKey).toBool();
    qDebug() << "  Receive Own:" << m_device->configurationParameter(QCanBusDevice::ReceiveOwnKey).toBool();
}