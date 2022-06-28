#include "MavlinkMissionReadRequest.h"

MavlinkMissionReadRequest::MavlinkMissionReadRequest(QObject *parent)
    : MissionReadRequest{parent}, MavlinkRequest(), m_state(State::GET_SIZE)
{
    resetTimers(300);
}

MavlinkMissionReadRequest::~MavlinkMissionReadRequest()
{

}

bool MavlinkMissionReadRequest::ready()
{
    if (m_state == State::UNDEFINED)
        return false;
    return MavlinkRequest::ready();
}

mavlink_message_t MavlinkMissionReadRequest::construct()
{
    mavlink_message_t request;
    switch (m_state) {
    case State::GET_SIZE:
        mavlink_msg_mission_request_list_pack(GCSID, COMPID, &request, APID, APCOMP, MAV_MISSION_TYPE_MISSION);
        break;
    case State::GET_NEXT:
        mavlink_msg_mission_request_int_pack(GCSID, COMPID, &request, APID, APCOMP, m_nextPoint, MAV_MISSION_TYPE_MISSION);
        break;
    case State::SET_ACK:
        mavlink_msg_mission_ack_pack(GCSID, COMPID, &request, APID, APCOMP, MAV_RESULT_ACCEPTED, MAV_MISSION_TYPE_MISSION);
        break;
    default:
        break;
    }
    return request;
}

bool MavlinkMissionReadRequest::processMessage(const mavlink_message_t &msg)
{
    if (m_state == State::UNDEFINED)
        return false;
    switch (msg.msgid) {
    case MAVLINK_MSG_ID_HEARTBEAT: {
        mavlink_heartbeat_t hb;
        mavlink_msg_heartbeat_decode(&msg, &hb);
        break;
    }
    case MAVLINK_MSG_ID_MISSION_COUNT: {
        mavlink_mission_count_t count;
        mavlink_msg_mission_count_decode(&msg, &count);
        if (count.mission_type == MAV_MISSION_TYPE_MISSION) {
            m_missinFull = count.count;
            m_nextPoint = 0;
            m_state = State::GET_NEXT;
            resetTimers(100);
            emit progress(0);
            qDebug() << "request " << m_missinFull << " points...";
            return true;
        }
        break;
    }
    case MAVLINK_MSG_ID_MISSION_ITEM_INT: {
        mavlink_mission_item_int_t item;
        mavlink_msg_mission_item_int_decode(&msg, &item);
        if (item.mission_type == MAV_MISSION_TYPE_MISSION) {
            switch (item.command) {
            case MAV_CMD_NAV_WAYPOINT:
                emit onItem(item.seq, PointType::SIMPLE_POINT,
                            item.param1, item.param2, item.param3, item.param4,
                            (double)item.x / 1.e7, (double)item.y / 1.e7, (double)item.z / 1000.);
                break;
            default:
                break;
            }
            // next
            m_nextPoint++;
            emit progress(m_nextPoint / m_missinFull);
            if (m_nextPoint >= m_missinFull)
            {
                // ack
                m_state = State::SET_ACK;
                emit progress(1.);
                resetTimers(300);
            } else {
                resetTimers(100);
            }
            return true;
        }
        break;
    }
    case MAVLINK_MSG_ID_MISSION_ACK: {
        mavlink_mission_ack_t ack;
        mavlink_msg_mission_ack_decode(&msg, &ack);
        if (ack.mission_type == MAV_MISSION_TYPE_MISSION) {
            if (ack.type == MAV_RESULT_IN_PROGRESS) {
                // wait
            } else if (ack.type == MAV_RESULT_ACCEPTED) {
                switch (m_state) {
                case State::GET_SIZE:
                    return true;
                case State::GET_NEXT:
                    return true;
                default:
                    break;
                }
            } else {
                switch (m_state) {
                case State::GET_SIZE:
                    m_state = State::UNDEFINED;
                    // emit onError(ERR_FAILED_GET_COUNT);
                    return true;
                case State::GET_NEXT:
                    m_state = State::UNDEFINED;
                    // emit onError(ERR_FAILED_GET_INDEX);
                    return true;
                default:
                    break;
                }
            }
        }
        break;
    }
    }
    return false;
}

void MavlinkMissionReadRequest::onInit()
{

}

void MavlinkMissionReadRequest::resetTimers(int interval)
{
    m_maxMessageLiveTimeMs = 2000;
    m_messageIntervalMs = interval;
    m_dirty = true;
}
