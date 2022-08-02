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

void MavlinkMissionWriteRequest::set(const QList<MissionItem> &items)
{
    int seq = 0;
    for (auto x : items)
    {
        mavlink_message_t request_int;
        mavlink_message_t request;
        switch (x.type) {
        case MissionItem::ItemType::SIMPLE_POINT: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, getFrameInt(x.frame),
                                              MAV_CMD_NAV_WAYPOINT, false, true, qIsNaN(x.param_1) ? 0 : x.param_1, 0, 0, 0,
                                              (int32_t)(x.param_x * 1.e7),
                                              (int32_t)(x.param_y * 1.e7),
                                              (float)x.param_z, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                          seq, getFrame(x.frame),
                                          MAV_CMD_NAV_WAYPOINT, false, true, qIsNaN(x.param_1) ? 0 : x.param_1, 0, 0, 0,
                                          (float)x.param_x,
                                          (float)x.param_y,
                                          (float)x.param_z, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::HOME: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, getFrameInt(x.frame),
                                              MAV_CMD_DO_SET_HOME, false, true, 1, 0, 0, 0, 0, 0,
                                              0, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                          seq, getFrame(x.frame),
                                          MAV_CMD_DO_SET_HOME, false, true, 1, 0, 0, 0, 0, 0,
                                          0, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::TAKEOFF: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, getFrameInt(x.frame),
                                              MAV_CMD_NAV_TAKEOFF, false, true, 0, 0, 0, 0, 0, 0,
                                              (float)x.param_z, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, getFrame(x.frame),
                                              MAV_CMD_NAV_TAKEOFF, false, true, 0, 0, 0, 0, 0, 0,
                                              (float)x.param_z, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::RTL: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_NAV_RETURN_TO_LAUNCH, false, true, 0, 0, 0,
                                              0, 0, 0, 0, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_NAV_RETURN_TO_LAUNCH, false, true, 0, 0, 0,
                                              0, 0, 0, 0, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::LAND: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, getFrameInt(x.frame),
                                              MAV_CMD_NAV_LAND, false, true, 0, 0, 0, 0,
                                              (int32_t)(x.param_x * 1.e7),
                                              (int32_t)(x.param_y * 1.e7),
                                              0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, getFrame(x.frame),
                                              MAV_CMD_NAV_LAND, false, true, 0, 0, 0, 0,
                                              x.param_x,
                                              x.param_y,
                                              0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::JUMP: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_JUMP, false, true, x.param_1, x.param_2,
                                              0, 0, 0, 0, 0, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_JUMP, false, true, x.param_1, x.param_2,
                                              0, 0, 0, 0, 0, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::DELAY: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_CONDITION_DELAY, false, true, x.param_1, 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_CONDITION_DELAY, false, true, x.param_1, 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::DISTANCE: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_CONDITION_DISTANCE, false, true, x.param_1, 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_CONDITION_DISTANCE, false, true, x.param_1, 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::SPEED: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_CHANGE_SPEED, false, true, 1, x.param_1, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_CHANGE_SPEED, false, true, 1, x.param_1, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::SET_SERVO: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_SET_SERVO, false, true, x.param_1, x.param_2, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_SET_SERVO, false, true, x.param_1, x.param_2, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::ROI: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, getFrameInt(x.frame),
                                              MAV_CMD_DO_SET_ROI, false, true, 0, 0, 0, 0,
                                              (int32_t)(x.param_x * 1.e7),
                                              (int32_t)(x.param_y * 1.e7),
                                              (float)(x.param_z * 1000.), MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, getFrame(x.frame),
                                              MAV_CMD_DO_SET_ROI, false, true, 0, 0, 0, 0,
                                              x.param_x,
                                              x.param_y,
                                              x.param_z, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::CAMERA: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_DIGICAM_CONTROL, false, true, 0, x.param_2,
                                              0, 0, x.param_x, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_DIGICAM_CONTROL, false, true, 0, x.param_2,
                                              0, 0, x.param_x, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::GIMBAL: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_MOUNT_CONTROL, false, true, x.param_1,
                                              x.param_2, x.param_3, 0, 0, 0,
                                              0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_MOUNT_CONTROL, false, true, x.param_1,
                                              x.param_2, x.param_3, 0, 0, 0,
                                              0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::TRIGGER: {
            int pt = (x.param_1 < 1 && x.param_2 < 1) ? 0 : 1;
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_SET_CAM_TRIGG_DIST, false, true,
                                              x.param_1, x.param_2, pt,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_SET_CAM_TRIGG_DIST, false, true,
                                              x.param_1, x.param_2, pt,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        case MissionItem::ItemType::PARACHUTE: {
            mavlink_msg_mission_item_int_pack(GCSID, COMPID, &request_int, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_PARACHUTE, false, true, 1, 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            mavlink_msg_mission_item_pack(GCSID, COMPID, &request, APID, APCOMP,
                                              seq, MAV_FRAME_MISSION,
                                              MAV_CMD_DO_PARACHUTE, false, true, 1, 0, 0,
                                              0, 0, 0, 0.f, MAV_MISSION_TYPE_MISSION);
            break;
        }
        default:
            break;
        }
        m_mission_int.append(request_int);
        m_mission.append(request);
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
        else {
            request = m_mission.at(m_nextPoint);
            mavlink_mission_item_t it;
            mavlink_msg_mission_item_decode(&request, &it);
            qDebug() << "Write item " << it.command;
        }
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
            emit progress(m_nextPoint / m_mission.size(), false);
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
            emit progress(m_nextPoint / m_mission.size(), false);
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
            if (m_state == State::SET_SIZE || m_state == State::SET_NEXT) {
                switch (ack.type) {
                case MAV_MISSION_ERROR:
                    if (m_state == State::SET_SIZE)
                        emit onError(tr("Undefined error while write mission size"));
                    else
                        emit onError(tr("Undefined error while write mission item"));
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
                    emit onError(tr("Invalid sequence while write mission"));
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
            qDebug() << "mission ack " << ack.type;
            if (ack.type == MAV_RESULT_IN_PROGRESS) {
                // continue
            } else if (ack.type == MAV_MISSION_ACCEPTED) {
                // done
                emit progress(1., false);
                m_state = State::UNDEFINED;
            } else {
                emit progress(0., true);
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

int MavlinkMissionWriteRequest::getFrame(MissionItem::Frame f)
{
    switch (f) {
    case MissionItem::Frame::FRAME_ABSOLUTE:
        return MAV_FRAME_GLOBAL;
    case MissionItem::Frame::FRAME_RELATIVE:
        return MAV_FRAME_GLOBAL_RELATIVE_ALT;
    case MissionItem::Frame::FRAME_RELIEF:
        return MAV_FRAME_GLOBAL_TERRAIN_ALT;
    default:
        break;
    }
    return MAV_FRAME_MISSION;
}

int MavlinkMissionWriteRequest::getFrameInt(MissionItem::Frame f)
{
    switch (f) {
    case MissionItem::Frame::FRAME_ABSOLUTE:
        return MAV_FRAME_GLOBAL_INT;
    case MissionItem::Frame::FRAME_RELATIVE:
        return MAV_FRAME_GLOBAL_RELATIVE_ALT_INT;
    case MissionItem::Frame::FRAME_RELIEF:
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
