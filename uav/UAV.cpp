#include "UAV.h"
UAV::UAV(DataStreamer *streamer, QObject *parent)
    : QObject{parent},
    m_streamer(streamer)
{
    m_connection = new Connection(this);
    connect(m_connection, &Connection::onReadyData, m_streamer, &DataStreamer::onDataReceived);

    connect(m_streamer, &DataStreamer::writeData, m_connection, &Connection::writeData);


    m_positioning = new Positioning(m_streamer);
    m_sensors = new Sensors(m_streamer);
    m_mission = new Mission(m_streamer);

    doRequestHomePosition();
}

Connection *UAV::connection() const
{
    return m_connection;
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

Positioning *UAV::getPositioning() const
{
    return m_positioning;
}

Sensors *UAV::getSensors() const
{
    return m_sensors;
}

Mission *UAV::getMission() const
{
    return m_mission;
}

void UAV::doRequestHomePosition() {
    HomePositionRequest *streamer = m_streamer->createHomePositionRequest();
    connect(streamer, &HomePositionRequest::onHomePositionChanged, this, &UAV::setHomePosition);
}

int UAV::controlMode() const
{
    return m_controlMode;
}

void UAV::setControlMode(int newControlMode)
{
    if (m_controlMode == newControlMode)
        return;
    m_controlMode = newControlMode;
    emit controlModeChanged();
}

void UAV::doARM() const
{
    m_streamer->createARMRequest(ARMRequest::Mode::ARM);
}

void UAV::doDisARM() const
{
    m_streamer->createARMRequest(ARMRequest::Mode::DISARM);
}

void UAV::doTakeoff() const
{
    m_streamer->createARMRequest(ARMRequest::Mode::TAKEOFF);
}

void UAV::doLand() const
{
    m_streamer->createManualControlRequest()->doLand();
}

void UAV::doRTL() const
{
    m_streamer->createManualControlRequest()->doRTL();
}

void UAV::doGuided() const
{
    if (m_positioning->position().isValid())
        m_streamer->createManualControlRequest()->goTo(m_positioning->position());
}

void UAV::doMission() const
{
    m_streamer->createManualControlRequest()->doMission();
}
