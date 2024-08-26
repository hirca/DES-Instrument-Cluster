#ifndef IDASHBOARDBRIDGE_H
#define IDASHBOARDBRIDGE_H

#include <QObject>
#include <QCanBusDevice>

class IDashboardBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(int rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(QString gear READ gear NOTIFY gearChanged)
    Q_PROPERTY(int batteryLevel READ batteryLevel NOTIFY batteryLevelChanged)

public:
    explicit IDashboardBridge(QObject *parent = nullptr);
    ~IDashboardBridge();

    int speed() const;
    int rpm() const;
    QString gear() const;
    int batteryLevel() const;

signals:
    void speedChanged();
    void rpmChanged();
    void gearChanged();
    void batteryLevelChanged();

private slots:
    void initialize();
    void processReceivedFrames();

private:
    bool connectToCANBus();
    void processCANFrame(const QCanBusFrame &frame);

    QCanBusDevice *m_canDevice;
    int m_speed;
    int m_rpm;
    QString m_gear;
    int m_batteryLevel;

    static const quint32 CAN_FRAME_ID = 0x123;
};

#endif // IDASHBOARDBRIDGE_H