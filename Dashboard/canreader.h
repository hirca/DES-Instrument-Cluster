// canreader.h
#ifndef CANREADER_H
#define CANREADER_H

#include <QObject>
#include <QCanBusDevice>
#include <QTimer>
#include <QVector>

/**
 * @brief The CANReader class handles CAN bus communication and processes vehicle data
 * 
 * This class manages the connection to a CAN bus device and processes incoming CAN frames
 * to extract vehicle information such as RPM, speed, and gear state. It implements
 * signal smoothing through a moving average filter for RPM readings.
 */
class CANReader : public QObject
{
    Q_OBJECT
    // Expose properties to QML
    Q_PROPERTY(int rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(QString gearState READ gearState NOTIFY gearStateChanged)

public:
    explicit CANReader(QObject *parent = nullptr);
    ~CANReader();

    // Getter methods for QML properties
    int rpm() const;
    double speed() const;
    QString gearState() const;

signals:
    void rpmChanged();      ///< Emitted when RPM value changes
    void speedChanged();    ///< Emitted when speed value changes
    void gearStateChanged();///< Emitted when gear state changes

private slots:
    void processReceivedFrames();  ///< Processes incoming CAN frames
    void updateRPM();              ///< Updates RPM and dependent values

private:
    // CAN device setup and management
    void setupCANDevice();

    // RPM processing methods
    void addRPMReading(int rpm);
    int calculateAverageRPM() const;
    
    // Vehicle state calculation methods
    void calculateSpeed();
    void updateGearState();

    // Device management
    QCanBusDevice *m_device;   ///< Pointer to CAN bus device
    QTimer *m_timer;           ///< Timer for periodic updates

    // Vehicle state variables
    int m_rpm;                 ///< Current filtered RPM value
    int m_lastReceivedRPM;     ///< Last raw RPM value received
    double m_speed;            ///< Calculated vehicle speed in km/h
    QString m_gearState;       ///< Current gear state (N or D)

    // RPM filtering parameters and data
    static const int FILTER_SIZE = 10;  ///< Size of moving average filter
    QVector<int> m_rpmReadings;         ///< Circular buffer for RPM readings
    int m_rpmSum;                       ///< Running sum for moving average

    // Physical constants for calculations
    static constexpr double WHEEL_DIAMETER = 0.065;  ///< Wheel diameter in meters
    static constexpr double WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * M_PI;
    static constexpr double GEAR_RATIO = 0.04;       ///< Transmission gear ratio
};

#endif // CANREADER_H