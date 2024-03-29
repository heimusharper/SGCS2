#include "Positioning.h"

Positioning::Positioning(QObject *parent)
    : QObject{parent}
{

}

Positioning::Positioning(DataStreamer *streamer, QObject *parent)
    : QObject{parent},
    m_streamer(streamer)
{
    PositionDataStream *positionStream = m_streamer->getPositionDataStream();
    connect(positionStream, &PositionDataStream::onPositionChanged, this, &Positioning::setPosition);
    connect(positionStream, &PositionDataStream::onAttitudeChanged, this, &Positioning::setAttitude);
    connect(positionStream, &PositionDataStream::onTargetChanged, this, &Positioning::setTargetPosition);

}

const QGeoCoordinate &Positioning::position() const
{
    return m_position;
}

void Positioning::setPosition(const QGeoCoordinate &newPosition)
{
    if (m_position == newPosition)
        return;
    //qDebug() <<"on change position" << newPosition;
    m_position = newPosition;
    emit positionChanged();
}

const QVector3D &Positioning::attitude() const
{
    return m_attitude;
}

void Positioning::setAttitude(const QVector3D &newAttitude)
{
    if (m_attitude == newAttitude)
        return;
    m_attitude = newAttitude;
    emit attitudeChanged();
}

const QGeoCoordinate &Positioning::targetPosition() const
{
    return m_targetPosition;
}

void Positioning::setTargetPosition(const QGeoCoordinate &newTargetPosition)
{
    if (m_targetPosition == newTargetPosition)
        return;
    m_targetPosition = newTargetPosition;
    emit targetPositionChanged();
}
