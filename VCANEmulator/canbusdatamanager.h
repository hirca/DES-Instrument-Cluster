#ifndef CANBUSDATAMANAGER_H
#define CANBUSDATAMANAGER_H

#include <QObject>
#include <QTimer>
#include <QCanBusDevice>

class CANBusDataManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString speedCANId READ speedCANId WRITE setSpeedCANId NOTIFY speedCANIdChanged)
    Q_PROPERTY(QString rpmCANId READ rpmCANId WRITE setRpmCANId NOTIFY rpmCANIdChanged)
    Q_PROPERTY(QString gearCANId READ gearCANId WRITE setGearCANId NOTIFY gearCANIdChanged)
    Q_PROPERTY(QString batteryCANId READ batteryCANId WRITE setBatteryCANId NOTIFY batteryCANIdChanged)
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(int speedUpdateInterval READ speedUpdateInterval WRITE setSpeedUpdateInterval NOTIFY speedUpdateIntervalChanged)
    Q_PROPERTY(int rpmUpdateInterval READ rpmUpdateInterval WRITE setRpmUpdateInterval NOTIFY rpmUpdateIntervalChanged)

public:
    explicit CANBusDataManager(QObject *parent = nullptr);
    ~CANBusDataManager();

    QString speedCANId() const;
    void setSpeedCANId(const QString &id);

    QString rpmCANId() const;
    void setRpmCANId(const QString &id);

    QString gearCANId() const;
    void setGearCANId(const QString &id);

    QString batteryCANId() const;
    void setBatteryCANId(const QString &id);

    bool isRunning() const;

    int speedUpdateInterval() const;
    void setSpeedUpdateInterval(int interval);

    int rpmUpdateInterval() const;
    void setRpmUpdateInterval(int interval);

public slots:
    void setSpeedRange(int min, int max);
    void setSpeedProfile(bool increasing);
    void setSpeedStepSize(int step);

    void setRPMRange(int min, int max);
    void setRPMProfile(bool increasing);
    void setRPMStepSize(int step);

    void setGear(const QString &gear);
    void setBatteryLevel(int level);

    void start();
    void stop();

signals:
    void speedCANIdChanged();
    void rpmCANIdChanged();
    void gearCANIdChanged();
    void batteryCANIdChanged();
    void isRunningChanged();
    void speedUpdateIntervalChanged();
    void rpmUpdateIntervalChanged();

private:
    void sendCANMessage(const QString &id, const QByteArray &data);
    void updateSpeed();
    void updateRPM();
    bool connectToCANBus();
    void sendInitialValues();

    QString m_speedCANId;
    QString m_rpmCANId;
    QString m_gearCANId;
    QString m_batteryCANId;

    int m_minSpeed;
    int m_maxSpeed;
    bool m_speedIncreasing;
    int m_speedStepSize;
    int m_currentSpeed;

    int m_minRPM;
    int m_maxRPM;
    bool m_rpmIncreasing;
    int m_rpmStepSize;
    int m_currentRPM;

    QString m_currentGear;
    int m_batteryLevel;

    QTimer m_speedTimer;
    QTimer m_rpmTimer;
    bool m_isRunning;

    QCanBusDevice *m_canDevice;

    int m_speedUpdateInterval;
    int m_rpmUpdateInterval;
};

#endif // CANBUSDATAMANAGER_H
