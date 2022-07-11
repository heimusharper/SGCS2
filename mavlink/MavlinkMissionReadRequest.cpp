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
            emit progress(0);
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
        qDebug() << "received point" << item.command << m_missinFull << item.param1 << item.param2 << item.param3 << item.param4;
        if (item.mission_type == MAV_MISSION_TYPE_MISSION) {
            switch (item.command) {
            case MAV_CMD_NAV_WAYPOINT:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::SIMPLE_POINT);
                it->setPosition(QGeoCoordinate((double)item.x / 1.e7, (double)item.y / 1.e7, (double)item.z / 1000.));
                it->setFrame(getFrame(item.frame));
                it->setDelayOnWaypoint((int)item.param1);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_NAV_TAKEOFF:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::TAKEOFF);
                it->setPosition(QGeoCoordinate(0, 0, (double)item.z));
                it->setFrame(getFrame(item.frame));
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::RTL);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_NAV_LAND:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::LAND);
                it->setPosition(QGeoCoordinate((double)item.x / 1.e7, (double)item.y / 1.e7, 0));
                it->setFrame(getFrame(item.frame));
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_JUMP:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::JUMP);
                it->setJumpTo(item.param1);
                it->setJumpRepeats(item.param2);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_CONDITION_DELAY:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::DELAY);
                it->setDelayOnWaypoint(item.param1);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_CONDITION_DISTANCE:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::DISTANCE);
                it->setDistance(item.param1);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_CHANGE_SPEED:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::SPEED);
                it->setSpeed(item.param2);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_SET_SERVO:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::SET_SERVO);
                it->setServo(item.param1);
                it->setPwm(item.param2);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_SET_ROI:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::ROI);
                it->setPosition(QGeoCoordinate((double)item.x / 1.e7, (double)item.y / 1.e7, (double)item.z / 1000.));
                it->setFrame(getFrame(item.frame));
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_DIGICAM_CONTROL:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::CAMERA);
                it->setZoomPosition(item.param2);
                if ((int)item.param4 == 0) {
                } else if ((int)item.param4 == 1) {
                    it->setAutofocusNow(true);
                }
                if ((int)item.x == 0){
                } else if ((int)item.x == 1)
                    it->setShoot(true);
                else if ((int)item.x == 2)
                    it->setRecordStart(1);
                else if ((int)item.x == 3)
                    it->setRecordStart(-1);
                // it->setRecordStart(item.param2);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_MOUNT_CONTROL:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::GIMBAL);
                it->setGimbalPitch(item.param1);
                it->setGimbalRoll(item.param2);
                it->setGimbalYaw(item.param3);
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_SET_CAM_TRIGG_DIST:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::TRIGGER);
                if (item.param3 < 1) {
                    it->setShootOnDistance(0);
                    it->setShootOnTime(0);
                } else {
                    it->setShootOnDistance(item.param1);
                    it->setShootOnTime(item.param2);
                }
                emit onItem(item.seq, it);
                break;
            }
            case MAV_CMD_DO_PARACHUTE:
            {
                MissionItem *it = new MissionItem;
                it->setType((int)MissionItem::ItemType::PARACHUTE);
                emit onItem(item.seq, it);
            }
            default:
                break;
            }
            // next
            m_nextPoint = item.seq + 1;
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

int MavlinkMissionReadRequest::getFrame(int f)
{
    switch (f) {
    case MAV_FRAME_GLOBAL:
    case MAV_FRAME_GLOBAL_INT:
        return (int)MissionItem::Frame::ABSOLUTE;
    case MAV_FRAME_GLOBAL_RELATIVE_ALT:
    case MAV_FRAME_GLOBAL_RELATIVE_ALT_INT:
        return (int)MissionItem::Frame::RELATIVE;
    case MAV_FRAME_GLOBAL_TERRAIN_ALT:
    case MAV_FRAME_GLOBAL_TERRAIN_ALT_INT:
        return (int)MissionItem::Frame::RELIEF;
    default:
        break;
    }
    return (int)MissionItem::Frame::INVALID;
}

void MavlinkMissionReadRequest::resetTimers(int interval)
{
    m_maxMessageLiveTimeMs = 2000;
    m_messageIntervalMs = interval;
    m_dirty = true;
}
