#ifndef UAV_H
#define UAV_H

#include <QObject>
#include "../streamer/DataStreamer.h"
#include "Positioning.h"
#include "Sensors.h"
#include "Mission.h"

#include "connection/Connection.h"


class UAV : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate homePosition READ homePosition WRITE setHomePosition NOTIFY homePositionChanged)
    Q_PROPERTY(int controlMode READ controlMode WRITE setControlMode NOTIFY controlModeChanged)
    Q_PROPERTY(float progress READ progress WRITE setProgress NOTIFY progressChanged)

public:
    enum ControlMode {
        UNSUPORTED,
        WAIT,
        ARMED,
        TAKEOFF,
        GUIDED,
        GUIDED_RC,
        AUTO,
        RTL,
        LAND,
        FOLOW
    };
    Q_ENUM(ControlMode)

    explicit UAV(DataStreamer *streamer, QObject *parent = nullptr);

    Q_INVOKABLE Connection *connection() const;

    const QGeoCoordinate &homePosition() const;
    void setHomePosition(const QGeoCoordinate &newHomePosition);

    Q_INVOKABLE Positioning *getPositioning() const;
    Q_INVOKABLE Sensors *getSensors() const;
    Q_INVOKABLE Mission *getMission() const;

    int controlMode() const;
    void setControlMode(int newControlMode);

    Q_INVOKABLE void doARM() const;
    Q_INVOKABLE void doDisARM() const;
    Q_INVOKABLE void doTakeoff() const;

    Q_INVOKABLE void doLand() const;
    Q_INVOKABLE void doRTL() const;
    Q_INVOKABLE void doGuided() const;
    Q_INVOKABLE void doMission() const;

    float progress() const;

public slots:

    Q_INVOKABLE void doRequestHomePosition();

    void setProgress(float newProgress);
private:

    // connection
    Connection *m_connection = nullptr;

    // streamer
    DataStreamer *m_streamer = nullptr;

    // objs
    Positioning *m_positioning = nullptr;

    // sensors
    Sensors *m_sensors = nullptr;

    // mission
    Mission *m_mission = nullptr;

    // parameters
    QGeoCoordinate m_homePosition;

    int m_controlMode = (int)ControlMode::WAIT;

    float m_progress;

signals:

    void homePositionChanged(const QGeoCoordinate &pos);
    void controlModeChanged();
    void progressChanged();
};

#endif // UAV_H
