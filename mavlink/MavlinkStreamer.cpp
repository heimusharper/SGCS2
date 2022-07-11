#include "MavlinkStreamer.h"

MavlinkStreamer::MavlinkStreamer(QObject *parent)
    : DataStreamer{parent}
{
    auto main = getMainStream();
    connect(dynamic_cast<MavlinkMainDataStream*>(main),
            &MavlinkMainDataStream::onFoundAutopilot, [this](
                uint8_t sysid, uint8_t compid, ModeHelper::APMode mode){
                AP_ID = sysid;
                AP_COMPID = compid;
                AP_MODE = mode;
                m_initiated = true;

                if (m_pingRequest)
                    m_pingRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
                if (m_homePositionRequest)
                    m_homePositionRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
                if (m_armRequest)
                    m_armRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
                if (m_mainDataStream)
                    m_mainDataStream->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
                if (m_positionDataStream)
                    m_positionDataStream->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
                if (m_sensorsDataStream)
                    m_sensorsDataStream->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
                if (m_manualControlRequest)
                    m_manualControlRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
                if (m_missionReadRequest)
                    m_missionReadRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
                if (m_missionWriteRequest)
                    m_missionWriteRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
            });

    m_pingRequest = new MavlinkPingRequest();

    m_ioTimer = new QTimer(this);
    connect(m_ioTimer, &QTimer::timeout, this, &MavlinkStreamer::tryWriteData);
    m_ioTimer->start(50);
}

MavlinkStreamer::~MavlinkStreamer() {
    if (m_homePositionRequest)
        m_homePositionRequest->deleteLater();
    if (m_armRequest)
        m_armRequest->deleteLater();
    delete m_pingRequest;
}

PositionDataStream *MavlinkStreamer::getPositionDataStream()
{
    if (!m_positionDataStream) {
        m_positionDataStream = new MavlinkPositionDataStream(this);
        if (m_initiated)
            m_positionDataStream->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
    }
    return m_positionDataStream;
}

SensorsDataStream *MavlinkStreamer::getSensorsStream()
{
    if (!m_sensorsDataStream) {
        m_sensorsDataStream = new MavlinkSensorsDataStream(this);
        if (m_initiated)
            m_sensorsDataStream->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
    }
    return m_sensorsDataStream;
}

HomePositionRequest *MavlinkStreamer::createHomePositionRequest()
{
    if (m_homePositionRequest) {
        m_homePositionRequest->deleteLater();
        m_homePositionRequest = nullptr;
    }
    m_homePositionRequest = new MavlinkHomePositionRequest(this);
    if (m_initiated)
        m_homePositionRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
    return m_homePositionRequest;
}

ARMRequest *MavlinkStreamer::createARMRequest(ARMRequest::Mode mode)
{
    if (m_armRequest) {
        m_armRequest->deleteLater();
        m_armRequest = nullptr;
    }
    m_armRequest = new MavlinkARMRequest(mode, this);
    if (m_initiated)
        m_armRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
    return m_armRequest;
}

ManualControlRequest *MavlinkStreamer::createManualControlRequest()
{
    if (!m_manualControlRequest) {
        m_manualControlRequest = new MavlinkManualControlRequest(this);
        if (m_initiated)
            m_manualControlRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
    }
    return m_manualControlRequest;
}

MissionReadRequest *MavlinkStreamer::createMissionReadRequest()
{
    if (m_missionReadRequest)
    {
        m_missionReadRequest->deleteLater();
        m_missionReadRequest = nullptr;
    }
    if (m_missionWriteRequest)
        m_missionWriteRequest->stop();
    m_missionReadRequest = new MavlinkMissionReadRequest(this);
    if (m_initiated)
        m_missionReadRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
    return m_missionReadRequest;
}

MissionWriteRequest *MavlinkStreamer::createMissionWriteRequest()
{
    if (m_missionWriteRequest)
    {
        m_missionWriteRequest->deleteLater();
        m_missionWriteRequest = nullptr;
    }
    if (m_missionReadRequest)
        m_missionReadRequest->stop();
    m_missionWriteRequest = new MavlinkMissionWriteRequest(this);
    if (m_initiated)
        m_missionWriteRequest->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
    return m_missionWriteRequest;
}

MainDataStream *MavlinkStreamer::getMainStream()
{
    if (!m_mainDataStream) {
        m_mainDataStream = new MavlinkMainDataStream(this);
        if (m_initiated)
            m_mainDataStream->init(GCS_ID, GCS_COMPID, AP_ID, AP_COMPID, AP_MODE);
    }
    return m_mainDataStream;

}

void MavlinkStreamer::onDataReceived(const QByteArray &data)
{
    mavlink_message_t msg;
    mavlink_status_t status;
    for (int i = 0; i < data.size(); i++) {
        if (mavlink_parse_char(MAVLINK_CHANEL, data.at(i), &msg, &status) != 0)
        {
            if (m_pingRequest)
                m_pingRequest->responce(msg);
            //str
            if (m_mainDataStream)
                m_mainDataStream->responce(msg);
            if (m_manualControlRequest)
                m_manualControlRequest->responce(msg);
            if (m_positionDataStream)
                m_positionDataStream->responce(msg);
            if (m_sensorsDataStream)
                m_sensorsDataStream->responce(msg);
            // rq
            if (m_homePositionRequest)
                m_homePositionRequest->responce(msg);
            if (m_armRequest)
                m_armRequest->responce(msg);
            if (m_missionReadRequest)
                m_missionReadRequest->responce(msg);
            if (m_missionWriteRequest)
                m_missionWriteRequest->responce(msg);
        }
    }
}

void MavlinkStreamer::tryWriteData()
{

    /*if (m_mainDataStream)
        m_mainDataStream->responce(msg);
    if (m_positionDataStream)
        m_positionDataStream->responce(msg);
    if (m_sensorsDataStream)
        m_sensorsDataStream->responce(msg);*/
    // rq
    if (m_pingRequest && m_pingRequest->ready())
        transmit(m_pingRequest->request());
    if (m_initiated) {
        if (m_homePositionRequest && m_homePositionRequest->ready())
            transmit(m_homePositionRequest->request());
        if (m_armRequest && m_armRequest->ready())
            transmit(m_armRequest->request());
        if (m_manualControlRequest && m_manualControlRequest->ready())
            transmit(m_manualControlRequest->request());
        if (m_missionReadRequest && m_missionReadRequest->ready())
            transmit(m_missionReadRequest->request());
        if (m_missionWriteRequest && m_missionWriteRequest->ready())
            transmit(m_missionWriteRequest->request());
    }
}

void MavlinkStreamer::transmit(const mavlink_message_t &msg)
{
    QByteArray out;
    out.resize(/*mavlink_max_message_length(&msg)*/ MAVLINK_MAX_PACKET_LEN);
    uint16_t realSize = mavlink_msg_to_send_buffer((uint8_t *)out.data(), &msg);
    out = out.left(realSize);
    emit writeData(out);
}
