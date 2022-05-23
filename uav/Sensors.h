#ifndef SENSORS_H
#define SENSORS_H

#include <QObject>
#include <QGeoCoordinate>
#include "../streamer/DataStreamer.h"
#include <QDebug>

class Sensors : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int gpsStatus READ gpsStatus WRITE setGpsStatus NOTIFY gpsStatusChanged)
public:
    enum GpsStatus {
        NA,
        ERROR,
        FIX2D,
        FIX3D,
        DGPS,
        RTKFLOAT,
        RTKFIX,
        STATIC,
        PPP
    };
    Q_ENUMS(GpsStatus)

    explicit Sensors(QObject *parent = nullptr);
    explicit Sensors(DataStreamer *streamer, QObject *parent = nullptr);

    int gpsStatus() const;
    void setGpsStatus(int newGpsStatus);

private:

    DataStreamer *m_streamer = nullptr;

    int m_gpsStatus = (int)GpsStatus::NA;

signals:
    void gpsStatusChanged();
};

#endif // SENSORS_H
