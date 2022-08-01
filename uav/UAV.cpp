#include "UAV.h"
UAV::UAV(DataStreamer *streamer, QObject *parent)
    : QObject{parent},
    m_streamer(streamer)
{
    //
    MainDataStream *mds = m_streamer->getMainStream();
    connect(mds, &MainDataStream::onControlModeChanged, this, [this](int i) {
        switch (i) {
        case (int)MainDataStream::ControlMode::WAIT:
            setControlMode(ControlMode::WAIT);
            break;
        case (int)MainDataStream::ControlMode::ARMED:
            setControlMode(ControlMode::ARMED);
            break;
        case (int)MainDataStream::ControlMode::TAKEOFF:
            setControlMode(ControlMode::TAKEOFF);
            break;
        case (int)MainDataStream::ControlMode::GUIDED:
            setControlMode(ControlMode::GUIDED);
            break;
        case (int)MainDataStream::ControlMode::GUIDED_RC:
            setControlMode(ControlMode::GUIDED_RC);
            break;
        case (int)MainDataStream::ControlMode::AUTO:
            setControlMode(ControlMode::AUTO);
            break;
        case (int)MainDataStream::ControlMode::RTL:
            setControlMode(ControlMode::RTL);
            break;
        case (int)MainDataStream::ControlMode::LAND:
            setControlMode(ControlMode::LAND);
            break;
        case (int)MainDataStream::ControlMode::FOLOW:
            setControlMode(ControlMode::FOLOW);
            break;
        case (int)MainDataStream::ControlMode::UNSUPORTED:
            setControlMode(ControlMode::UNSUPORTED);
            break;
        default:
            break;
        }
    });

    m_positioning = new Positioning(m_streamer, this);
    m_sensors = new Sensors(m_streamer, this);
    m_mission = new Mission(m_streamer, this);

    connect(m_mission, &Mission::progress, this, &UAV::setProgress);
    connect(this, &UAV::homePositionChanged, m_mission, &Mission::setHome);


    // data connection
    m_connection = new Connection(this);
    connect(m_connection, &Connection::onReadyData, m_streamer, &DataStreamer::onDataReceived);
    connect(m_streamer, &DataStreamer::writeData, m_connection, &Connection::writeData);


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
    m_mission->setHome(m_homePosition);
    emit homePositionChanged(m_homePosition);
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
    qDebug() << "SET CONTROL MODE " << newControlMode;
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
    if (m_mission->isEmpty())
        m_streamer->createARMRequest(ARMRequest::Mode::TAKEOFF);
    else
        m_streamer->createARMRequest(ARMRequest::Mode::MISSION_START);
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

float UAV::progress() const
{
    return m_progress;
}

void UAV::setProgress(float newProgress)
{
    if (qFuzzyCompare(m_progress, newProgress))
        return;
    m_progress = newProgress;
    emit progressChanged();
}
