#ifndef UAV_H
#define UAV_H

#include <QObject>
#include "../streamer/DataStreamer.h"
#include "Positioning.h"
#include "Sensors.h"
#include "connection/Connection.h"


class UAV : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate homePosition READ homePosition WRITE setHomePosition NOTIFY homePositionChanged)
    Q_PROPERTY(int controlMode READ controlMode WRITE setControlMode NOTIFY controlModeChanged)

public:
    enum ControlMode {
        WAIT,
        GUIDED,
        AUTO,
        RTL,
        LAND
    };
    Q_ENUMS(ControlMode)

    explicit UAV(DataStreamer *streamer, QObject *parent = nullptr);

    Q_INVOKABLE Connection *connection() const;

    const QGeoCoordinate &homePosition() const;
    void setHomePosition(const QGeoCoordinate &newHomePosition);

    Q_INVOKABLE Positioning *getPositioning() const;
    Q_INVOKABLE Sensors *getSensors() const;

    int controlMode() const;
    void setControlMode(int newControlMode);

public slots:

    Q_INVOKABLE void doRequestHomePosition();

private:

    // connection
    Connection *m_connection = nullptr;

    // streamer
    DataStreamer *m_streamer = nullptr;

    // objs
    Positioning *m_positioning = nullptr;

    // sensors
    Sensors *m_sensors = nullptr;

    // parameters
    QGeoCoordinate m_homePosition;

    int m_controlMode = (int)ControlMode::WAIT;

signals:

    void homePositionChanged();
    void controlModeChanged();
};

#endif // UAV_H
