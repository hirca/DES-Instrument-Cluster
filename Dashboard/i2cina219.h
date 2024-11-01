// i2cina219.h
#ifndef I2CINA219_H
#define I2CINA219_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <map>

/**
 * @brief The I2CIna219 class handles communication with the INA219 battery monitoring IC
 * 
 * This class manages I2C communication with an INA219 power monitoring IC to read
 * battery voltage and calculate remaining battery capacity (State of Charge).
 * It provides periodic updates and low battery warnings.
 */
class I2CIna219 : public QObject {
    Q_OBJECT
    Q_PROPERTY(int level READ level NOTIFY batteryChanged)
    Q_PROPERTY(NOTIFY lowBatteryWarning)

public:
    explicit I2CIna219(QObject *parent = nullptr);
    ~I2CIna219();

    /**
     * @brief Initialize I2C communication
     * @return true if initialization successful, false otherwise
     */
    bool initI2C();

    /**
     * @brief Read current battery voltage
     */
    void readBusVoltage();

    /**
     * @brief Get current battery level percentage
     * @return Battery level (0-100)
     */
    int level();

    /**
     * @brief Calculate State of Charge from voltage
     * @param voltage Battery voltage
     * @return Battery State of Charge percentage
     */
    double get_battery_soc(double voltage);

signals:
    void batteryChanged();      ///< Emitted when battery level changes
    void lowBatteryWarning();   ///< Emitted when battery level is critically low

private:
    // I2C communication parameters
    static constexpr const char* DEFAULT_I2C_DEVICE = "/dev/i2c-1";
    static constexpr int DEFAULT_I2C_ADDRESS = 0x41;
    static constexpr int BUS_VOLTAGE_REGISTER = 0x02;
    static constexpr double VOLTAGE_LSB = 0.004;  // 4mV per bit
    static constexpr double LOW_BATTERY_THRESHOLD = 10.8;
    
    const char* device;         ///< I2C device path
    int ina219Address;         ///< I2C device address
    int busVoltageRegister;    ///< Register address for voltage reading
    int file;                  ///< File descriptor for I2C device
    int m_level;               ///< Current battery level percentage
    QTimer* timer;             ///< Timer for periodic updates
};

#endif // I2CINA219_H