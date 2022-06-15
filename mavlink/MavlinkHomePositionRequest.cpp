#include "MavlinkHomePositionRequest.h"

MavlinkHomePositionRequest::MavlinkHomePositionRequest(QObject *parent)
    : HomePositionRequest(parent)
{
}

bool MavlinkHomePositionRequest::ready()
{
    if (m_gpsFixType >= GPS_FIX_TYPE_3D_FIX)
        return MavlinkRequest::ready();
    return false;
}

mavlink_message_t MavlinkHomePositionRequest::construct()
{
    return m_request;
}

bool MavlinkHomePositionRequest::processMessage(const mavlink_message_t &msg)
{    switch (msg.msgid)
    {
    case MAVLINK_MSG_ID_GPS_RAW_INT: {
        mavlink_gps_raw_int_t gps;
        mavlink_msg_gps_raw_int_decode(&msg, &gps);
        m_gpsFixType = gps.fix_type;
        return true;
    }
    case MAVLINK_MSG_ID_HOME_POSITION:
    {
        mavlink_home_position_t home;
        mavlink_msg_home_position_decode(&msg, &home);
        if (m_gpsFixType >=  GPS_FIX_TYPE_3D_FIX) {
            QGeoCoordinate pos;
            pos.setLatitude((qreal)home.latitude / 10.e7);
            pos.setLongitude((qreal)home.longitude / 10.e7);
            pos.setAltitude((qreal)home.altitude / 1000.);
            m_empty = true;
            qDebug() << "home position received";
            emit onHomePositionChanged(pos);
        }
        return true;
    }
    }
    return false;
}

void MavlinkHomePositionRequest::onInit()
{
    // predefined
    /*mavlink_msg_command_long_pack_chan(
        GCSID, COMPID, 0, &m_request, APID, APCOMP,
        MAV_CMD_GET_HOME_POSITION, 0, 0, 0, 0, 0, 0, 0, 0);*/
    mavlink_msg_command_long_pack_chan(
        GCSID, COMPID, 0, &m_request, APID, APCOMP,
        MAV_CMD_REQUEST_MESSAGE, 0, MAVLINK_MSG_ID_HOME_POSITION, 0, 0, 0, 0, 0, 0);
}
