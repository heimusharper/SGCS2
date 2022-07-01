#ifndef SENSORSSDATATREAM_H
#define SENSORSSDATATREAM_H

#include <QObject>
#include <QGeoCoordinate>

class SensorsDataStream : public QObject
{
    Q_OBJECT
public:
    enum GpsStatus {
        NA,
        ERR,
        FIX2D,
        FIX3D,
        DGPS,
        RTKFLOAT,
        RTKFIX,
        STATIC,
        PPP
    };
    explicit SensorsDataStream(QObject *parent = nullptr)
        : QObject(parent)
    {

    }
    virtual ~SensorsDataStream() = default;
signals:

    void onGPSStateChanged(int state);
};

#endif // SENSORSSTREAMER_H
