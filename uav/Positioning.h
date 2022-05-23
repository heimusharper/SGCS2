#ifndef POSITIONING_H
#define POSITIONING_H

#include <QObject>
#include <QGeoCoordinate>
#include "../streamer/DataStreamer.h"

class Positioning : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D attitude READ attitude WRITE setAttitude NOTIFY attitudeChanged)
public:
    explicit Positioning(DataStreamer *streamer, QObject *parent = nullptr);

    const QGeoCoordinate &position() const;
    void setPosition(const QGeoCoordinate &newPosition);

    const QVector3D &attitude() const;
    void setAttitude(const QVector3D &newAttitude);

private:

    DataStreamer *m_streamer = nullptr;

    // params
    QGeoCoordinate m_position;

    QVector3D m_attitude;

signals:

    void positionChanged();
    void attitudeChanged();
};

#endif // POSITIONING_H
