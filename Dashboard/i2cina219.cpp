#include "i2cina219.h"

// Voltage to State of Charge lookup table
static const std::map<float, float> voltage_to_soc = {
    {12.4, 100.0},
    {12.2, 90.0},
    {12.0, 80.0},
    {11.8, 70.0},
    {11.6, 60.0},
    {11.4, 50.0},
    {11.2, 40.0},
    {11.0, 30.0},
    {10.8, 20.0},
    {10.6, 10.0},
    {10.0, 5.0},
    {9.0, 0.0}
};

I2CIna219::I2CIna219(QObject *parent)
    : QObject(parent)
    , device(DEFAULT_I2C_DEVICE)
    , ina219Address(DEFAULT_I2C_ADDRESS)
    , busVoltageRegister(BUS_VOLTAGE_REGISTER)
    , file(-1)
    , m_level(0)
{
    // Initialize I2C communication
    initI2C();

    // Set up periodic battery level updates
    timer = new QTimer(this);
    timer->start(10000);  // Update every 10 seconds
    connect(timer, &QTimer::timeout, this, &I2CIna219::readBusVoltage);
}

I2CIna219::~I2CIna219()
{
    if (file >= 0) {
        close(file);
    }
}

bool I2CIna219::initI2C()
{
    // Open I2C device
    file = open(device, O_RDWR);
    if (file < 0) {
        qDebug() << "Cannot open I2C device:" << device;
        return false;
    }

    // Set I2C slave address
    if (ioctl(file, I2C_SLAVE, ina219Address) < 0) {
        qDebug() << "Failed to set I2C slave address:" << ina219Address;
        close(file);
        file = -1;
        return false;
    }

    return true;
}

double I2CIna219::get_battery_soc(double voltage)
{
    // Handle boundary conditions
    if (voltage >= 12.4) return 100.0;
    if (voltage <= 9.0) return 0.0;

    // Find voltage range in lookup table
    auto it_high = voltage_to_soc.lower_bound(voltage);
    if (it_high == voltage_to_soc.end()) return 0.0;

    auto it_low = std::prev(it_high);

    // Linear interpolation between voltage points
    float v_high = it_high->first;
    float soc_high = it_high->second;
    float v_low = it_low->first;
    float soc_low = it_low->second;

    return soc_low + (soc_high - soc_low) * (voltage - v_low) / (v_high - v_low);
}

int I2CIna219::level()
{
    return m_level;
}

void I2CIna219::readBusVoltage()
{
    if (file < 0) {
        qDebug() << "I2C device not initialized";
        return;
    }

    // Write register address to read from
    char buf[2] = {busVoltageRegister};
    if (write(file, buf, 1) != 1) {
        qDebug() << "Failed to write to I2C device";
        return;
    }

    // Read voltage data
    if (read(file, buf, 2) != 2) {
        qDebug() << "Failed to read from I2C device";
        return;
    }

    // Convert raw data to voltage
    int16_t rawVoltage = (buf[0] << 8) | buf[1];
    rawVoltage >>= 3;  // 13-bit resolution
    double busVoltage = rawVoltage * VOLTAGE_LSB;

    // Update battery level and emit changes
    int newLevel = static_cast<int>(get_battery_soc(busVoltage));
    if (m_level != newLevel) {
        m_level = newLevel;
        emit batteryChanged();
    }

    // Check for low battery condition
    if (busVoltage <= LOW_BATTERY_THRESHOLD) {
        emit lowBatteryWarning();
    }
}