#include "MavlinkPhotoModeRequest.h"

MavlinkPhotoModeRequest::MavlinkPhotoModeRequest(float time, float dst, QObject *parent)
    : PhotoModeRequest(time, dst, parent), MavlinkRequest()
{

}

bool MavlinkPhotoModeRequest::ready()
{
    return MavlinkRequest::ready();
}

mavlink_message_t MavlinkPhotoModeRequest::construct()
{
    mavlink_message_t message;
    mavlink_msg_command_long_pack(GCSID, COMPID, &message,
                                  APID, APCOMP, MAV_CMD_DO_SET_CAM_TRIGG_DIST,
                                  m_distance, m_time * 10., 0, 0, 0, 0, 0, 0);
    qDebug() << "Set photo mode  d " << m_distance << " t " << m_time;

    emit onSet(m_time, m_distance);
    return message;
}

bool MavlinkPhotoModeRequest::processMessage(const mavlink_message_t &msg)
{
    switch (msg.msgid) {
        case MAVLINK_MSG_ID_COMMAND_ACK: {
            mavlink_command_ack_t ack;
            mavlink_msg_command_ack_decode(&msg, &ack);
            if (ack.command == MAV_CMD_DO_SET_CAM_TRIGG_DIST) {
                if (ack.result == MAV_RESULT_ACCEPTED) {
                    m_empty = true;
                    emit onSet(m_time, m_distance);
                }
                return true;
            }
            break;
        }
    }
    return false;
}

void MavlinkPhotoModeRequest::onInit()
{

}
