#include "PhotoPayload.h"

PhotoPayload::PhotoPayload(QObject *parent)
    : QAbstractListModel{parent}
{

}

PhotoPayload::PhotoPayload(DataStreamer *streamer, QObject *parent)
    : QAbstractListModel{parent},
    m_streamer(streamer)
{
    connect(m_streamer->getPhotoPayloadStream(), &PhotoPayloadStream::onTakeShot, [this]
            (int index, const QGeoCoordinate &pos) {
        m_photos.append(Photo(pos));
        setFullCount(index + 1);
    });
}

void PhotoPayload::commit(float time, float dst)
{
    if (m_streamer) {
        auto rq =  m_streamer->createPhotoModeRequest(time, dst);
        connect(rq, &PhotoModeRequest::onSet, this, [this](float t, float d){
            setOnTime(t);
            setOnDistance(d);
        });
    }
}

void PhotoPayload::takeShot()
{
    if (m_streamer) {
        m_streamer->getPhotoPayloadStream()->takeOneShot();
    }
}

int PhotoPayload::rowCount(const QModelIndex &) const
{
    return m_photos.size();
}

QHash<int, QByteArray> PhotoPayload::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Latitude] = "lat";
    roles[Longitude] = "lon";
    roles[Altitude] = "alt";

    return roles;
}

QVariant PhotoPayload::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Latitude:
        return m_photos.at(index.row()).pos.latitude();
    case Longitude:
        return m_photos.at(index.row()).pos.longitude();
    case Altitude:
        return m_photos.at(index.row()).pos.altitude();
    default:
        break;
    }
    return QVariant();
}

float PhotoPayload::onTime() const
{
    return m_onTime;
}

void PhotoPayload::setOnTime(float newOnTime)
{
    if (qFuzzyCompare(m_onTime, newOnTime))
        return;
    m_onTime = newOnTime;
    emit onTimeChanged();
}

float PhotoPayload::onDistance() const
{
    return m_onDistance;
}

void PhotoPayload::setOnDistance(float newOnDistance)
{
    qDebug() << "SET ON DISTANCE" << newOnDistance;
    if (qFuzzyCompare(m_onDistance, newOnDistance))
        return;
    m_onDistance = newOnDistance;
    emit onDistanceChanged();
}

int PhotoPayload::fullCount() const
{
    return m_fullCount;
}

void PhotoPayload::setFullCount(int newFullCount)
{
    if (m_fullCount == newFullCount)
        return;
    m_fullCount = newFullCount;
    emit fullCountChanged();
}
