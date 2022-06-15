#include "MavlinkManualControlRequest.h"

MavlinkManualControlRequest::MavlinkManualControlRequest(QObject *parent)
    : ManualControlRequest{parent}, MavlinkRequest()
{

}

bool MavlinkManualControlRequest::ready()
{
    if (m_stateSet == StateSet::UNDEFINED)
        return false;
    return MavlinkRequest::ready();
}

void MavlinkManualControlRequest::doLand() {
    m_stateSet = StateSet::LAND;
    reset();
}

void MavlinkManualControlRequest::doRTL() {
    m_stateSet = StateSet::RTL;
    reset();
}

void MavlinkManualControlRequest::doMission() {
    m_stateSet = StateSet::MISSION;
    reset();
}

void MavlinkManualControlRequest::goTo(const QGeoCoordinate &pos) {
    m_targetPos = pos;
    if (m_isPositioning)
        m_stateSet = StateSet::SET_POSITION;
    else
        m_stateSet = StateSet::GUIDED;
    reset();
}

void MavlinkManualControlRequest::reset() {
    m_maxMessageLiveTimeMs = 2000;
    m_messageIntervalMs = (m_stateSet == StateSet::UNDEFINED) ? 100 : 1000;
    if (m_stateSet == StateSet::UNDEFINED)
        m_empty = true;
    else
        m_dirty = true;
}

mavlink_message_t MavlinkManualControlRequest::construct()
{
    mavlink_message_t message;
    switch (m_stateSet) {
    case StateSet::LAND: {
        qDebug() << "Land...";
        mavlink_msg_set_mode_pack(GCSID, COMPID, &message, APID,
                                  ModeHelper::getBaseMode(APMODE),
                                  ModeHelper::getModeLand(APMODE));
        break;
    }
    case StateSet::MISSION: {
        qDebug() << "Auto...";
        mavlink_msg_set_mode_pack(GCSID, COMPID, &message, APID,
                                  ModeHelper::getBaseMode(APMODE),
                                  ModeHelper::getModeAuto(APMODE));
        break;
    }
    case StateSet::RTL: {
        qDebug() << "Auto...";
        mavlink_msg_set_mode_pack(GCSID, COMPID, &message, APID,
                                  ModeHelper::getBaseMode(APMODE),
                                  ModeHelper::getModeRTL(APMODE));
        break;
    }
    case StateSet::GUIDED: {
        qDebug() << "Guided...";
        mavlink_msg_set_mode_pack(GCSID, COMPID, &message, APID,
                                  ModeHelper::getBaseMode(APMODE),
                                  ModeHelper::getModeGuided(APMODE));
        break;
    }
    case StateSet::SET_POSITION: {
        qDebug() << "Set position...";

        std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> now = std::chrono::system_clock::now();
        uint32_t compensate = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastBootMessage).count();
        const uint16_t mask = 0b0000101111111000;
        mavlink_msg_set_position_target_global_int_pack(GCSID,
                                                         COMPID,
                                                         &message,
                                                         m_bootTime + compensate,
                                                         APID,
                                                         0,
                                                         MAV_FRAME_GLOBAL_RELATIVE_ALT_INT,
                                                         mask,
                                                         (int)(m_targetPos.latitude() * 1e7),
                                                         (int)(m_targetPos.longitude() * 1e7),
                                                         m_targetPos.altitude(),
                                                         0,
                                                         0,
                                                         0,
                                                         0,
                                                         0,
                                                         0,
                                                         0,
                                                         0);

        break;
    }
    default:
        break;
    }
    return message;
}

bool MavlinkManualControlRequest::processMessage(const mavlink_message_t &msg)
{

    switch (msg.msgid) {
    case MAVLINK_MSG_ID_SYSTEM_TIME:{
        mavlink_system_time_t sys;
        mavlink_msg_system_time_decode(&msg, &sys);
        m_bootTime = sys.time_boot_ms;
        m_lastBootMessage = std::chrono::system_clock::now();
        break;
    }
    case MAVLINK_MSG_ID_HEARTBEAT: {
        mavlink_heartbeat_t hb;
        mavlink_msg_heartbeat_decode(&msg, &hb);
        m_isPositioning = hb.custom_mode == ModeHelper::getModeGuided(APMODE);
        break;
    }
    case MAVLINK_MSG_ID_COMMAND_ACK: {
        mavlink_command_ack_t ack;
        mavlink_msg_command_ack_decode(&msg, &ack);

        if (m_stateSet == StateSet::LAND && ack.command == MAVLINK_MSG_ID_SET_MODE)
        {
            if (ack.result == MAV_RESULT_ACCEPTED) {
                m_empty = true;
            } else {

            }
        }
        if (m_stateSet == StateSet::MISSION && ack.command == MAVLINK_MSG_ID_SET_MODE)
        {
            if (ack.result == MAV_RESULT_ACCEPTED) {
                m_empty = true;
            } else {

            }
        }
        if (m_stateSet == StateSet::RTL && ack.command == MAVLINK_MSG_ID_SET_MODE)
        {
            if (ack.result == MAV_RESULT_ACCEPTED) {
                m_empty = true;
            } else {

            }
        }
        /*if (m_stateSet == StateSet::SET_POSITION && ack == MAVLINK_MSG_ID_SET_MODE)
        {
            if (ack.result == MAV_RESULT_ACCEPTED) {
                m_empty = true;
            } else {

            }
        }*/
        if (m_stateSet == StateSet::GUIDED && ack.command == MAVLINK_MSG_ID_SET_MODE)
        {
            if (ack.result == MAV_RESULT_ACCEPTED) {
                m_isPositioning = true;
                goTo(m_targetPos);
            } else {

            }
        }

        break;
    }
    }
    return false;
}

void MavlinkManualControlRequest::onInit()
{

}
