#ifndef IDASHBOARDBRIDGE_H
#define IDASHBOARDBRIDGE_H

#include <QObject>
#include <QCanBusDevice>

/**
 * @brief The IDashboardBridge class
 *
 * This class serves as a bridge between the CAN bus and the dashboard UI.
 * It reads CAN frames, interprets the data, and provides updated values
 * for various vehicle parameters such as speed, RPM, gear, and battery level.
 */
class IDashboardBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(int rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(QString gear READ gear NOTIFY gearChanged)
    Q_PROPERTY(int batteryLevel READ batteryLevel NOTIFY batteryLevelChanged)

public:
    /**
     * @brief Constructor for IDashboardBridge
     * @param parent The parent QObject (default is nullptr)
     */
    explicit IDashboardBridge(QObject *parent = nullptr);

    /**
     * @brief Destructor for IDashboardBridge
     */
    ~IDashboardBridge();

    // Getter methods for vehicle parameters
    int speed() const { return m_speed; }
    int rpm() const { return m_rpm; }
    QString gear() const { return m_gear; }
    int batteryLevel() const { return m_batteryLevel; }

signals:
    // Signals to notify of parameter changes
    void speedChanged();
    void rpmChanged();
    void gearChanged();
    void batteryLevelChanged();

private slots:
    /**
     * @brief Processes incoming CAN frames
     * @param frame The received CAN frame
     */
    void processCANFrame(const QCanBusFrame &frame);

    /**
     * @brief Initializes the CAN bus connection
     */
    void initialize();

private:
    // CAN frame IDs for various vehicle parameters
    static const quint32 SPEED_FRAME_ID = 0x0CFF6F7;
    static const quint32 RPM_FRAME_ID = 0x0CFF6E7;
    static const quint32 GEAR_FRAME_ID = 0x0CFE6C00;
    static const quint32 BATTERY_FRAME_ID = 0x1801D0F3;

    /**
     * @brief Connects to the CAN bus
     * @return true if connection is successful, false otherwise
     */
    bool connectToCANBus();

    /**
     * @brief Processes a speed frame
     * @param frame The CAN frame containing speed data
     */
    void processSpeedFrame(const QCanBusFrame &frame);

    /**
     * @brief Processes an RPM frame
     * @param frame The CAN frame containing RPM data
     */
    void processRPMFrame(const QCanBusFrame &frame);

    /**
     * @brief Processes a gear frame
     * @param frame The CAN frame containing gear data
     */
    void processGearFrame(const QCanBusFrame &frame);

    /**
     * @brief Processes a battery frame
     * @param frame The CAN frame containing battery level data
     */
    void processBatteryFrame(const QCanBusFrame &frame);

    QCanBusDevice *m_canDevice;  ///< Pointer to the CAN bus device
    int m_speed;                 ///< Current vehicle speed
    int m_rpm;                   ///< Current engine RPM
    QString m_gear;              ///< Current gear position
    int m_batteryLevel;          ///< Current battery level
};

#endif // IDASHBOARDBRIDGE_H
