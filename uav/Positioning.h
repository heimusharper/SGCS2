#ifndef POSITIONING_H
#define POSITIONING_H

#include <QObject>
#include <QGeoCoordinate>
#include "../streamer/DataStreamer.h"
#include <QDebug>

class Positioning : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D attitude READ attitude WRITE setAttitude NOTIFY attitudeChanged)
    Q_PROPERTY(QGeoCoordinate targetPosition READ targetPosition WRITE setTargetPosition NOTIFY targetPositionChanged)
public:
    Positioning(QObject *parent = nullptr);
    explicit Positioning(DataStreamer *streamer, QObject *parent = nullptr);

    const QGeoCoordinate &position() const;

    const QVector3D &attitude() const;

    const QGeoCoordinate &targetPosition() const;

public slots:
    void setPosition(const QGeoCoordinate &newPosition);
    void setAttitude(const QVector3D &newAttitude);
    void setTargetPosition(const QGeoCoordinate &newTargetPosition);

private:

    DataStreamer *m_streamer = nullptr;

    // params
    QGeoCoordinate m_position;

    QVector3D m_attitude;

    QGeoCoordinate m_targetPosition;

signals:

    void positionChanged();
    void attitudeChanged();
    void targetPositionChanged();
};

#endif // POSITIONING_H
