#include "MavlinkPingRequest.h"

MavlinkPingRequest::MavlinkPingRequest()
    : MavlinkRequest{}
{
    m_messageIntervalMs = 500;
}

mavlink_message_t MavlinkPingRequest::construct()
{
    index = !index;
    if (index){
        mavlink_message_t msg;
        mavlink_msg_heartbeat_pack(GCSID, COMPID, &msg,
                                   MAV_TYPE_GCS, MAV_AUTOPILOT_INVALID, 0, 0, 0);
        return msg;
    }
    mavlink_message_t msg;
    mavlink_msg_ping_pack(GCSID, COMPID, &msg, (uint64_t)QTime::currentTime().msecsSinceStartOfDay() * 1000, m_pingSeq++, 0, 0);
    return msg;
}

bool MavlinkPingRequest::processMessage(const mavlink_message_t &msg)
{
    return false;
}

void MavlinkPingRequest::onInit()
{
}
