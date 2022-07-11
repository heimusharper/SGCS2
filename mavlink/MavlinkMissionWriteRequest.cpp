#include "MavlinkMissionWriteRequest.h"

MavlinkMissionWriteRequest::MavlinkMissionWriteRequest(QObject *parent)
    : MissionWriteRequest(parent), MavlinkRequest()
{
    resetTimers(300);
}

MavlinkMissionWriteRequest::~MavlinkMissionWriteRequest()
{

}

bool MavlinkMissionWriteRequest::ready()
{
    if (m_state == State::UNDEFINED)
        return false;
    return MavlinkRequest::ready();
}

void MavlinkMissionWriteRequest::set(const QList<MissionItem*> &items)
{
    int seq = 0;
    for (auto x : items)
    {
        mavlink_message_t request;
        mavlink_message_t request_int;
        switch (x->type()) {
        case (int)MissionItem::ItemType::SIMPLE_POINT: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, getFrameInt(x->frame()),
                                              MAV_CMD_NAV_WAYPOINT, false, true, x->delayOnWaypoint(), 0, 0, 0,
                                              (int32_t)(x->position().latitude() * 1.e7),
                                              (int32_t)(x->position().longitude() * 1.e7),
                                              (float)(x->position().altitude() * 1000.), MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, getFrame(x->frame()),
                                              MAV_CMD_NAV_WAYPOINT, false, true, x->delayOnWaypoint(), 0, 0, 0,
                                              x->position().latitude(),
                                              x->position().longitude(),
                                              x->position().altitude(), MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::TAKEOFF: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, getFrameInt(x->frame()),
                                              MAV_CMD_NAV_TAKEOFF, false, true, 0, 0, 0, 0, 0, 0,
                                              (float)x->position().altitude(), MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, getFrame(x->frame()),
                                              MAV_CMD_NAV_TAKEOFF, false, true, 0, 0, 0, 0, 0, 0,
                                              (float)x->position().altitude(), MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::RTL: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_NAV_RETURN_TO_LAUNCH, false, true, 0, 0, 0,
                                              0, 0, 0, 0, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_NAV_RETURN_TO_LAUNCH, false, true, 0, 0, 0,
                                              0, 0, 0, 0, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::LAND: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, getFrameInt(x->frame()),
                                              MAV_CMD_NAV_LAND, false, true, 0, 0, 0, 0,
                                              (int32_t)(x->position().latitude() * 1.e7),
                                              (int32_t)(x->position().longitude() * 1.e7),
                                              0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, getFrame(x->frame()),
                                              MAV_CMD_NAV_LAND, false, true, 0, 0, 0, 0,
                                              x->position().latitude(),
                                              x->position().longitude(),
                                              0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::JUMP: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_JUMP, false, true, x->jumpTo(), x->jumpRepeats(),
                                              0, 0, 0, 0, 0, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_JUMP, false, true, x->jumpTo(), x->jumpRepeats(),
                                              0, 0, 0, 0, 0, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::DELAY: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_CONDITION_DELAY, false, true, x->delayOnWaypoint(), 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_CONDITION_DELAY, false, true, x->delayOnWaypoint(), 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::DISTANCE: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_CONDITION_DISTANCE, false, true, x->distance(), 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_CONDITION_DISTANCE, false, true, x->distance(), 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::SPEED: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_CHANGE_SPEED, false, true, 1, x->speed(), 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_CHANGE_SPEED, false, true, 1, x->speed(), 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::SET_SERVO: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_SET_SERVO, false, true, x->servo(), x->pwm(), 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_SET_SERVO, false, true, x->servo(), x->pwm(), 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::ROI: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, getFrameInt(x->frame()),
                                              MAV_CMD_DO_SET_ROI, false, true, 0, 0, 0, 0,
                                              (int32_t)(x->position().latitude() * 1.e7),
                                              (int32_t)(x->position().longitude() * 1.e7),
                                              (float)(x->position().altitude() * 1000.), MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, getFrame(x->frame()),
                                              MAV_CMD_DO_SET_ROI, false, true, 0, 0, 0, 0,
                                              x->position().latitude(),
                                              x->position().longitude(),
                                              x->position().altitude(), MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::CAMERA: {
            int i = 0;
            if (x->recordStart() == 1)
                i = 2;
            else if (x->recordStart() == -1)
                i = 3;
            else if (x->shoot())
                i = 1;

            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_DIGICAM_CONTROL, false, true, 0, x->zoomPosition(),
                                              0, 0, i, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_DIGICAM_CONTROL, false, true, 0, x->zoomPosition(),
                                              0, 0, i, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::GIMBAL: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_MOUNT_CONTROL, false, true, x->gimbalPitch(),
                                              x->gimbalRoll(), x->gimbalYaw(), 0, 0, 0,
                                              0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_MOUNT_CONTROL, false, true, x->gimbalPitch(),
                                              x->gimbalRoll(), x->gimbalYaw(), 0, 0, 0,
                                              0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::TRIGGER: {
            int pt = (x->shootOnDistance() < 1 && x->shootOnTime() < 1) ? 0 : 1;
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_SET_CAM_TRIGG_DIST, false, true,
                                              x->shootOnDistance(), x->shootOnTime(), pt,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_SET_CAM_TRIGG_DIST, false, true,
                                              x->shootOnDistance(), x->shootOnTime(), pt,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case (int)MissionItem::ItemType::PARACHUTE: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_PARACHUTE, false, true, 1, 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_PARACHUTE, false, true, 1, 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        default:
            break;
        }
        m_mission.append(request);
        m_mission_int.append(request_int);
        seq++;
    }
    if (!m_mission.isEmpty()){
        m_state = State::SET_SIZE;
        resetTimers(300);
    }
    qDebug() << "write mission " << m_mission.size();
}

void MavlinkMissionWriteRequest::stop()
{
    m_state = State::UNDEFINED;
}

mavlink_message_t MavlinkMissionWriteRequest::construct()
{
    mavlink_message_t request;
    switch (m_state) {
    case State::SET_SIZE:
        qDebug() << "write mission size " << m_mission.size();
        mavlink_msg_mission_count_pack(GCSID, COMPID, &request, APID, APCOMP, m_mission.size(), MAV_MISSION_TYPE_MISSION);
        break;
    case State::SET_NEXT: {
        qDebug() << "write mission at " << m_nextPoint;
        if (m_useInt)
            request = m_mission_int.at(m_nextPoint);
        else
            request = m_mission.at(m_nextPoint);
        break;
    }
    default:
        break;
    }
    return request;
}

bool MavlinkMissionWriteRequest::processMessage(const mavlink_message_t &msg)
{
    if (m_state == State::UNDEFINED)
        return false;
    switch (msg.msgid) {
    case MAVLINK_MSG_ID_HEARTBEAT: {
        mavlink_heartbeat_t hb;
        mavlink_msg_heartbeat_decode(&msg, &hb);
        break;
    }
    case MAVLINK_MSG_ID_MISSION_REQUEST: {
        mavlink_mission_request_t i;
        mavlink_msg_mission_request_decode(&msg, &i);
        if (i.mission_type == MAV_MISSION_TYPE_MISSION)
        {
            m_nextPoint = i.seq;
            emit progress(m_nextPoint / m_mission.size());
            m_state = State::SET_NEXT;
            m_useInt = false;
            resetTimers(100);
            qDebug() << "Request i " << m_nextPoint;
            return true;
        }
        break;
    }
    case MAVLINK_MSG_ID_MISSION_REQUEST_INT: {
        mavlink_mission_request_int_t i;
        mavlink_msg_mission_request_int_decode(&msg, &i);
        if (i.mission_type == MAV_MISSION_TYPE_MISSION)
        {
            m_nextPoint = i.seq;
            emit progress(m_nextPoint / m_mission.size());
            m_state = State::SET_NEXT;
            m_useInt = true;
            resetTimers(100);
            qDebug() << "Request i int " << m_nextPoint;
            return true;
        }
        break;
    }
    case MAVLINK_MSG_ID_MISSION_ACK: {
        mavlink_mission_ack_t ack;
        mavlink_msg_mission_ack_decode(&msg, &ack);
        if (ack.mission_type == MAV_MISSION_TYPE_MISSION)
        {
            qDebug() << "mission ack " << ack.type;
            if (ack.type == MAV_MISSION_ACCEPTED) {
                // done
                emit progress(1.);
                m_state = State::UNDEFINED;
            } else {
                emit progress(0.);
                m_state = State::UNDEFINED;
                // failure
            }
            return true;
        }
        break;
    }
    }
    return false;
}

void MavlinkMissionWriteRequest::onInit()
{

}

int MavlinkMissionWriteRequest::getFrame(int f)
{
    switch (f) {
    case (int)MissionItem::Frame::ABSOLUTE:
        return MAV_FRAME_GLOBAL;
    case (int)MissionItem::Frame::RELATIVE:
        return MAV_FRAME_GLOBAL_RELATIVE_ALT;
    case (int)MissionItem::Frame::RELIEF:
        return MAV_FRAME_GLOBAL_TERRAIN_ALT;
    default:
        break;
    }
    return MAV_FRAME_MISSION;
}

int MavlinkMissionWriteRequest::getFrameInt(int f)
{
    switch (f) {
    case (int)MissionItem::Frame::ABSOLUTE:
        return MAV_FRAME_GLOBAL_INT;
    case (int)MissionItem::Frame::RELATIVE:
        return MAV_FRAME_GLOBAL_RELATIVE_ALT_INT;
    case (int)MissionItem::Frame::RELIEF:
        return MAV_FRAME_GLOBAL_TERRAIN_ALT_INT;
    default:
        break;
    }
    return MAV_FRAME_MISSION;
}

void MavlinkMissionWriteRequest::resetTimers(int interval)
{
    m_maxMessageLiveTimeMs = 2000;
    m_messageIntervalMs = interval;
    m_dirty = true;
}
