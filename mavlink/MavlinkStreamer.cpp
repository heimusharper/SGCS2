#include "MavlinkStreamer.h"

MavlinkStreamer::MavlinkStreamer(QObject *parent)
    : DataStreamer{parent}
{

}

MavlinkStreamer::~MavlinkStreamer() {
    delete m_positionDataStream;
    if (m_homePositionRequest)
        m_homePositionRequest->deleteLater();
}

PositionDataStream *MavlinkStreamer::getPositionDataStream()
{
    if (!m_positionDataStream)
        m_positionDataStream = new MavlinkPositionDataStream;
    return m_positionDataStream;
}

HomePositionRequest *MavlinkStreamer::createHomePositionRequest()
{
    if (m_homePositionRequest) {
        m_requests.removeAll(m_homePositionRequest);
        m_homePositionRequest->deleteLater();
    }
    m_homePositionRequest = new MavlinkHomePositionRequest();
    m_requests.push_back(m_homePositionRequest);
    return m_homePositionRequest;
}
