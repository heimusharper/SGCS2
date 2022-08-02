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

void MavlinkMissionReadRequest::stop()
{
    m_state = State::UNDEFINED;
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
            emit progress(0, false);
            qDebug() << "request " << m_missinFull << " points...";
            return true;
        }
        break;
    }
    case MAVLINK_MSG_ID_MISSION_ITEM_INT: {
        mavlink_mission_item_int_t item;
        mavlink_msg_mission_item_int_decode(&msg, &item);
        if (m_state == State::SET_ACK)
            return false;
        qDebug() << "received point" << item.command << m_missinFull << item.seq;
        qDebug() << "param" << item.param1 << item.param2 << item.param3 << item.param4 << item.x << item.y << item.z;
        if (item.mission_type == MAV_MISSION_TYPE_MISSION) {
            // ignore double received
            if (m_onReceived == item.seq)
                return false;
            else
                m_onReceived = item.seq;
            switch (item.command) {
            case MAV_CMD_NAV_WAYPOINT:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::SIMPLE_POINT;
                it.param_x = (double)item.x / 1.e7;
                it.param_y = (double)item.y / 1.e7;
                it.param_z = (double)item.z;
                it.frame = getFrame(item.frame);
                it.param_1 = item.param1;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_SET_HOME:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::HOME;
                it.param_x = (double)item.x;
                it.param_y = (double)item.y;
                it.param_z = (double)item.z;
                it.param_1 = item.param1;
                it.frame = getFrame(item.frame);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_NAV_TAKEOFF:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::TAKEOFF;
                it.param_x = 0.;
                it.param_y = 0.;
                it.param_z = (double)item.z;
                it.frame = getFrame(item.frame);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::RTL;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_NAV_LAND:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::LAND;
                it.param_x = (double)item.x / 1.e7;
                it.param_y = (double)item.y / 1.e7;
                it.param_z = 0;
                it.frame = getFrame(item.frame);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_JUMP:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::JUMP;
                it.param_1 = item.param1;
                it.param_2 = item.param2;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_CONDITION_DELAY:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::DELAY;
                it.param_1 = item.param1;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_CONDITION_DISTANCE:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::DISTANCE;
                it.param_1 = item.param1;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_CHANGE_SPEED:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::SPEED;
                it.param_1 = item.param2;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_SET_SERVO:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::SET_SERVO;
                it.param_1 = item.param1;
                it.param_2 = item.param2;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_SET_ROI:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::ROI;
                it.param_x = (double)item.x / 1.e7;
                it.param_y = (double)item.y / 1.e7;
                it.param_z = (double)item.z / 1000.;
                it.frame = getFrame(item.frame);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_DIGICAM_CONTROL:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::CAMERA;
                it.param_2 = item.param2;
                it.param_4 = item.param4;
                it.param_x = item.x;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_MOUNT_CONTROL:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::GIMBAL;
                it.param_1 = item.param1;
                it.param_2 = item.param2;
                it.param_3 = item.param3;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_SET_CAM_TRIGG_DIST:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::TRIGGER;
                it.param_1 = item.param1;
                it.param_2 = item.param2;
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_PARACHUTE:
            {
                MissionItem it;
                it.type = MissionItem::ItemType::PARACHUTE;
                emit onItem(item.seq, it);
            }
            default:
                break;
            }
            // next
            m_nextPoint = item.seq + 1;
            emit progress(m_nextPoint / m_missinFull, false);
            if (m_nextPoint >= m_missinFull)
            {
                // ack
                m_state = State::SET_ACK;
                emit progress(1., false);
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
                // continue
            } else if (ack.type == MAV_RESULT_ACCEPTED) {
                // continue
            } else {
                if (m_state == State::GET_NEXT || m_state == State::GET_SIZE) {
                    switch (ack.type) {
                    case MAV_MISSION_ERROR:
                        if (m_state == State::GET_SIZE)
                            emit onError(tr("Undefined error while read mission size"));
                        else
                            emit onError(tr("Undefined error while read mission item"));
                        break;
                    case MAV_MISSION_UNSUPPORTED_FRAME:
                        emit onError(tr("Unsupported frame"));
                        break;
                    case MAV_MISSION_UNSUPPORTED:
                        emit onError(tr("Mission operation is unsupported"));
                        break;
                    case MAV_MISSION_NO_SPACE:
                        emit onError(tr("Mission out of space"));
                        break;
                    case MAV_MISSION_INVALID:
                        emit onError(tr("Mission item %1 has invalid parameter").arg(m_nextPoint));
                        break;
                    case MAV_MISSION_INVALID_PARAM1:
                        emit onError(tr("Mission item %1 has invalid parameter 1").arg(m_nextPoint));
                        break;
                    case MAV_MISSION_INVALID_PARAM2:
                        emit onError(tr("Mission item %1 has invalid parameter 2").arg(m_nextPoint));
                        break;
                    case MAV_MISSION_INVALID_PARAM3:
                        emit onError(tr("Mission item %1 has invalid parameter 3").arg(m_nextPoint));
                        break;
                    case MAV_MISSION_INVALID_PARAM4:
                        emit onError(tr("Mission item %1 has invalid parameter 4").arg(m_nextPoint));
                        break;
                    case MAV_MISSION_INVALID_PARAM5_X:
                        emit onError(tr("Mission item %1 has invalid parameter 5/latitude").arg(m_nextPoint));
                        break;
                    case MAV_MISSION_INVALID_PARAM6_Y:
                        emit onError(tr("Mission item %1 has invalid parameter 6/longitude").arg(m_nextPoint));
                        break;
                    case MAV_MISSION_INVALID_PARAM7:
                        emit onError(tr("Mission item %1 has invalid parameter 7/altitude").arg(m_nextPoint));
                        break;
                    case MAV_MISSION_INVALID_SEQUENCE:
                        emit onError(tr("Invalid sequence while read mission"));
                        break;
                    case MAV_MISSION_DENIED:
                        emit onError(tr("Mission denied"));
                        break;
                    //case MAV_MISSION_OPERATION_CANCELLED:
                    //    emit onError(tr("Mission write canceled"));
                    //    break;
                    default:
                        break;
                    }
                }
                // failure
                emit progress(0., true);
                m_state = State::UNDEFINED;
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

MissionItem::Frame MavlinkMissionReadRequest::getFrame(int f)
{
    switch (f) {
    case MAV_FRAME_GLOBAL:
    case MAV_FRAME_GLOBAL_INT:
        return MissionItem::Frame::FRAME_ABSOLUTE;
    case MAV_FRAME_GLOBAL_RELATIVE_ALT:
    case MAV_FRAME_GLOBAL_RELATIVE_ALT_INT:
        return MissionItem::Frame::FRAME_RELATIVE;
    case MAV_FRAME_GLOBAL_TERRAIN_ALT:
    case MAV_FRAME_GLOBAL_TERRAIN_ALT_INT:
        return MissionItem::Frame::FRAME_RELIEF;
    default:
        break;
    }
    return MissionItem::Frame::FRAME_INVALID;
}

void MavlinkMissionReadRequest::resetTimers(int interval)
{
    m_maxMessageLiveTimeMs = 2000;
    m_messageIntervalMs = interval;
    m_dirty = true;
}
