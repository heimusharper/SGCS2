#include "MavlinkHomePositionRequest.h"

MavlinkHomePositionRequest::MavlinkHomePositionRequest(QObject *parent)
    : HomePositionRequest(parent)
{
}

mavlink_message_t MavlinkHomePositionRequest::construct()
{
    qDebug() << "request home";
    return m_request;
}

bool MavlinkHomePositionRequest::processMessage(const mavlink_message_t &msg)
{
    if (msg.msgid == MAVLINK_MSG_ID_HOME_POSITION)
    {
        mavlink_home_position_t home;
        mavlink_msg_home_position_decode(&msg, &home);
        QGeoCoordinate pos;
        pos.setLatitude((qreal)home.latitude / 10.e7);
        pos.setLongitude((qreal)home.longitude / 10.e7);
        pos.setAltitude((qreal)home.altitude / 1000.);
        emit onHomePositionChanged(pos);
        return true;
    }
    return false;
}

void MavlinkHomePositionRequest::onInit()
{
    // predefined
    mavlink_msg_command_long_pack_chan(
        GCSID, COMPID, 0, &m_request, APID, APCOMP,
        MAV_CMD_GET_HOME_POSITION, 0, 0, 0, 0, 0, 0, 0, 0);
}
