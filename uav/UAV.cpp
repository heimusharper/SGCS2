#include "UAV.h"
UAV::UAV(DataStreamer *streamer, QObject *parent)
    : QObject{parent},
    m_streamer(streamer)
{
    doRequestHomePosition();
}

const QGeoCoordinate &UAV::homePosition() const
{
    return m_homePosition;
}

void UAV::setHomePosition(const QGeoCoordinate &newHomePosition)
{
    if (m_homePosition == newHomePosition)
        return;
    m_homePosition = newHomePosition;
    emit homePositionChanged();
}

void UAV::doRequestHomePosition() {
    HomePositionRequest *streamer = m_streamer->createHomePositionRequest();
    connect(streamer, &HomePositionRequest::onHomePositionChanged, this, &UAV::setHomePosition);
}
