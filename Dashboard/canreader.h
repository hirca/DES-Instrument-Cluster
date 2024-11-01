// canreader.h
#ifndef CANREADER_H
#define CANREADER_H

#include <QObject>
#include <QCanBusDevice>
#include <QTimer>
#include <QVector>

class CANReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(QString gearState READ gearState NOTIFY gearStateChanged)

public:
    explicit CANReader(QObject *parent = nullptr);
    ~CANReader();

    int rpm() const;
    double speed() const;
    QString gearState() const;

signals:
    void rpmChanged();
    void speedChanged();
    void gearStateChanged();

private slots:
    void processReceivedFrames();
    void updateRPM();

private:
    void setupCANDevice();
    void addRPMReading(int rpm);
    int calculateAverageRPM() const;
    void calculateSpeed();
    void updateGearState();

    QCanBusDevice *m_device;
    QTimer *m_timer;
    int m_rpm;
    int m_lastReceivedRPM;
    double m_speed;
    QString m_gearState;

    static const int FILTER_SIZE = 10;  // Number of readings to average
    QVector<int> m_rpmReadings;
    int m_rpmSum;

    // Constants for speed calculation
    static constexpr double WHEEL_DIAMETER = 0.065;  // 6.5 cm in meters
    static constexpr double WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * M_PI;
    static constexpr double GEAR_RATIO = 0.04;  // gear ratio might use as scale factor
};

#endif // CANREADER_H
